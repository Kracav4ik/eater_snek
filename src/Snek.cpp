#include "Snek.h"

#include "params.h"
#include <QPainter>
#include <QCoreApplication>

SegmentRotation rotateLeft(SegmentRotation rotation){
    return SegmentRotation((rotation + 3) % 4);
}

SegmentRotation rotateRight(SegmentRotation rotation){
    return SegmentRotation((rotation + 1) % 4);
}

SegmentRotation rotate(SegmentRotation rotation, SegmentType direction) {
    if (direction == SegmentType::LEFT){
        return rotateLeft(rotation);
    } else if (direction == SegmentType::RIGHT) {
        return rotateRight(rotation);
    }
    return rotation;
}

struct SnekSegment{
    QPoint pos;
    SegmentType type;
    SegmentRotation rotation;

    SnekSegment(const QPoint& pos, SegmentType type, SegmentRotation rotation)
            : pos(pos), type(type), rotation(rotation) {}
};

void Snek::paint(QPainter& p) const {
    p.fillRect(GRID_SIZE, 2*GRID_SIZE, 5*GRID_SIZE, 3*GRID_SIZE, Qt::magenta);
    p.drawText(2*GRID_SIZE, 4*GRID_SIZE, "S N E K");
    for (int i = segments.size(); i > 0 ; --i) {
        const SnekSegment* segment = segments[i-1];
        paintSegment(*segment, p);
    }
}

QImage loadImage(const QString& path){
    QImage img(path);
    img = img.convertToFormat(QImage::Format_ARGB32);
    QRgb replace = qRgb(255, 0, 255);
    for (int x = 0; x < img.width(); ++x){
        for (int y = 0; y < img.height(); ++y){
            if (img.pixel(x, y) == replace){
                img.setPixel(x, y, Qt::transparent);
            }
        }
    }
    return img;
}

Snek::Snek(): QObject(nullptr), img(loadImage(QCoreApplication::applicationDirPath() + "/../data/snek_appal.png")) {
    segments.append(new SnekSegment({10+segments.size(),   10}, SegmentType::HEAD,  SegmentRotation::NONE));
    segments.append(new SnekSegment({10+segments.size(),   10}, SegmentType::LEFT,  SegmentRotation::CW_90));
    segments.append(new SnekSegment({10+segments.size()-1, 11}, SegmentType::RIGHT, SegmentRotation::NONE));
    segments.append(new SnekSegment({10+segments.size()-1, 11}, SegmentType::BODY,  SegmentRotation::NONE));
    segments.append(new SnekSegment({10+segments.size()-1, 11}, SegmentType::TAIL,  SegmentRotation::NONE));
}

Snek::~Snek() {
    for (SnekSegment* segment : segments) {
        delete segment;
    }
}

void Snek::paintSegment(const SnekSegment& segment, QPainter& p) const{
    p.save();
    p.translate(segment.pos*GRID_SIZE);
    QPoint center = QPoint(GRID_SIZE, GRID_SIZE) / 2;
    p.translate(center);
    p.rotate(segment.rotation * 90);
    p.translate(-center);
    p.drawImage(QPoint(), img, {{GRID_SIZE * segment.type, 0}, GRID_SIZE_2D});
    p.restore();
}

QPoint nextPos(const QPoint& pos, SegmentRotation rot){
    QPoint newPos;
    int x = pos.x();
    int y = pos.y();
    switch (rot){
        case SegmentRotation::NONE :
            newPos = QPoint(x - 1, y);
            break;
        case SegmentRotation::CW_90 :
            newPos = QPoint(x, y - 1);
            break;
        case SegmentRotation::CW_180 :
            newPos = QPoint(x + 1, y);
            break;
        case SegmentRotation::CW_270 :
            newPos = QPoint(x, y + 1);
            break;
    }
    return newPos;
}

void Snek::shrinkBody() {
    if (segments.size() > 2) {
        segments.removeLast();
        SnekSegment* last = segments.last();
        last->rotation = rotate(last->rotation, last->type);
        last->type = SegmentType::TAIL;
    }
}

void Snek::addHead(SegmentType direction) {
    SnekSegment* first = segments.first();
    SegmentRotation rot = rotate(first->rotation, direction);
    if(segments.size() == 1){
        first->rotation = rot;
    }
    else {
        first->type = direction;
    }
    SnekSegment* newSegment = new SnekSegment(nextPos(first->pos, rot), SegmentType::HEAD, rot);
    segments.prepend(newSegment);
}

void Snek::moveForward() {
    addHead(SegmentType::BODY);
}

void Snek::moveLeft() {
    addHead(SegmentType::LEFT);
}

void Snek::moveRight() {
    addHead(SegmentType::RIGHT);
}

void Snek::growUp() {
    addHead(SegmentType::BODY);
}

const QPoint& Snek::getHeadPos() {
    return segments.first()->pos;
}

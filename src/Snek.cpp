#include "Snek.h"

#include "params.h"
#include <QPainter>
#include <QCoreApplication>

SegmentRotation rotateLeft(SegmentRotation rotation){
    return SegmentRotation((static_cast<int>(rotation) + 3) % 4);
}

SegmentRotation rotateRight(SegmentRotation rotation){
    return SegmentRotation((static_cast<int>(rotation) + 1) % 4);
}

SegmentRotation combine(SegmentRotation r1, SegmentRotation r2) {
    switch (r1) {
        case SegmentRotation::NONE:
            return r2;
        case SegmentRotation::CW_90:
            return rotateRight(r2);
        case SegmentRotation::CW_180:
            return invert(r2);
        case SegmentRotation::CW_270:
            return rotateLeft(r2);
    }
}

int qHash(const SegmentRotation& p) {
    return static_cast<int>(p);
}

SegmentRotation rotate(SegmentRotation rotation, SegmentType direction) {
    if (direction == SegmentType::LEFT){
        return rotateLeft(rotation);
    } else if (direction == SegmentType::RIGHT) {
        return rotateRight(rotation);
    }
    return rotation;
}

SegmentRotation invert(SegmentRotation rot) {
    if (rot == SegmentRotation::CW_90) {
        return SegmentRotation::CW_270;
    }
    if (rot == SegmentRotation::CW_270) {
        return SegmentRotation::CW_90;
    }
    return rot;
}

QPoint rotatePoint(const QPoint& point, const QPoint& center, SegmentRotation rotation) {
    QPoint result = point - center;
    if (rotation == SegmentRotation::CW_90) {
        result = QPoint(-result.y(), result.x());
    }
    else if (rotation == SegmentRotation::CW_180) {
        result = QPoint(-result.x(), -result.y());
    }
    else if (rotation == SegmentRotation::CW_270) {
        result = QPoint(result.y(), -result.x());
    }
    return result + center;
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
    p.rotate(static_cast<int>(segment.rotation) * 90);
    p.translate(-center);
    p.drawImage(QPoint(), img, {{GRID_SIZE * static_cast<int>(segment.type), 0}, GRID_SIZE_2D});
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
    const QPoint& headNextPos = getHeadNextPos(direction);
    SnekSegment* first = segments.first();
    SegmentRotation rot = rotate(first->rotation, direction);
    if(segments.size() == 1){
        first->rotation = rot;
    }
    else {
        first->type = direction;
    }
    SnekSegment* newSegment = new SnekSegment(headNextPos, SegmentType::HEAD, rot);
    segments.prepend(newSegment);
}

const QPoint& Snek::getHeadPos() const {
    return segments.first()->pos;
}

SegmentRotation Snek::getHeadRotation() const {
    return segments.first()->rotation;
}

QPoint Snek::getHeadNextPos(SegmentType direction) const {
    SnekSegment* first = segments.first();
    SegmentRotation rot = rotate(first->rotation, direction);
    return nextPos(first->pos, rot);
}

QList<QPoint> Snek::getSegmentsPoints() const {
    QList<QPoint> points;
    for (SnekSegment* segment : segments) {
        points.append(segment->pos);
    }
    return points;
}

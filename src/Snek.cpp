#include "Snek.h"

#include "params.h"
#include <QPainter>

enum SegmentRotation{
    NONE,
    CW_90,
    CW_180,
    CW_270,
};
enum SegmentType{
    HEAD,
    BODY,
    BEND_UP,
    BEND_DOWN,
    TAIL
};

struct SnekSegment{
    const QPoint pos;
    const SegmentType type;
    const SegmentRotation rotation;

    SnekSegment(const QPoint& pos, SegmentType type, SegmentRotation rotation)
            : pos(pos), type(type), rotation(rotation) {}
};

void Snek::paint(QPainter& p) const {
    p.fillRect(GRID_SIZE, 2*GRID_SIZE, 5*GRID_SIZE, 3*GRID_SIZE, Qt::magenta);
    p.drawText(2*GRID_SIZE, 4*GRID_SIZE, "S N E K");
    p.drawImage(QPoint(), img, {0, 0, GRID_SIZE, GRID_SIZE});
    for (const SnekSegment* segment : segments) {
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

Snek::Snek(): QObject(nullptr), img(loadImage("../data/snek_appal.png")) {
    segments.append(new SnekSegment({segments.size(),   0}, SegmentType::HEAD,      SegmentRotation::NONE));
    segments.append(new SnekSegment({segments.size(),   0}, SegmentType::BEND_DOWN, SegmentRotation::CW_90));
    segments.append(new SnekSegment({segments.size()-1, 1}, SegmentType::BEND_UP,   SegmentRotation::NONE));
    segments.append(new SnekSegment({segments.size()-1, 1}, SegmentType::BODY,      SegmentRotation::NONE));
    segments.append(new SnekSegment({segments.size()-1, 1}, SegmentType::TAIL,      SegmentRotation::NONE));
}

Snek::~Snek() {
    for (SnekSegment* segment : segments) {
        delete segment;
    }
}

void Snek::paintSegment(const SnekSegment& segment, QPainter& p) const{
    p.save();
    p.translate(segment.pos*GRID_SIZE);
    p.translate(GRID_SIZE/2, GRID_SIZE/2);
    p.rotate(segment.rotation * 90);
    p.translate(-GRID_SIZE/2, -GRID_SIZE/2);
    p.drawImage(QPoint(), img, {GRID_SIZE * segment.type, 0, GRID_SIZE, GRID_SIZE});
    p.restore();
}

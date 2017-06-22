#include "Appal.h"

#include "params.h"

QImage loadImage(const QString& path);

void Appal::paint(QPainter& p) const {
    const QImage& img = loadImage("../data/snek_appal.png");
    p.drawImage(pos*GRID_SIZE, img, {{GRID_SIZE * APPAL, 0}, GRID_SIZE_2D});
}

Appal::Appal(const QPoint& pos): pos(pos){}

const QPoint& Appal::getPos() const {
    return pos;
}

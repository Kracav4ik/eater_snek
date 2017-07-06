#include "Appal.h"

#include "params.h"
#include <QImage>
#include <QPainter>

QImage loadImage(const QString& path);

void Appal::paint(QPainter& p) const {
    const QImage& img = loadImage("../data/snek_appal.png");
    p.drawImage(QRect(pos, UNIT_SIZE_2D), img, {{GRID_SIZE * APPAL, 0}, GRID_SIZE_2D});
}

Appal::Appal(const QPoint& pos): pos(pos){}

const QPoint& Appal::getPos() const {
    return pos;
}

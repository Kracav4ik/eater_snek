#include "Wall.h"

#include "params.h"

Wall::Wall(const QPoint& position)
        : position(position) {}

const QPoint& Wall::getPos() const {
    return position;
}

void Wall::paint(QPainter& p) const {
    p.fillRect(QRect(position, UNIT_SIZE_2D), Qt::darkCyan);
}

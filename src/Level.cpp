#include "Level.h"

#include "Snek.h"
#include "Wall.h"
#include "params.h"


Wall* Level::getWallAt(const QPoint& pos) const {
    if (!rect.contains(pos)) {
        return borderWall;
    }
    for (Wall* wall: _walls) {
        if (pos == wall->getPos()) {
            return wall;
        }
    }
    return nullptr;
}

void Level::removeOneWall(Wall* wall) {
    if (wall == borderWall) {
        return;
    }
    _walls.removeOne(wall);
    delete wall;
}

void Level::appendWall(Wall* wall) {
    _walls.append(wall);
}

Level::~Level() {
    for (Wall* wall : _walls) {
        delete wall;
    }
    delete borderWall;
}

Level::Level(const QRect& r): rect(r), borderWall(new Wall(QPoint())){}

void Level::paint(QPainter& painter) const {
    QPoint point = rect.topLeft();
    for (int i = 0; i < rect.width(); ++i) {
        painter.fillRect(QRect((point + QPoint(i, -1))*GRID_SIZE, GRID_SIZE_2D), Qt::darkGray);
        painter.fillRect(QRect((point + QPoint(i, rect.height()))*GRID_SIZE, GRID_SIZE_2D), Qt::darkGray);
    }
    for (int i = 0; i < rect.width(); ++i) {
        painter.fillRect(QRect((point + QPoint(-1, i))*GRID_SIZE, GRID_SIZE_2D), Qt::darkGray);
        painter.fillRect(QRect((point + QPoint(rect.width(), i))*GRID_SIZE, GRID_SIZE_2D), Qt::darkGray);
    }
    for (Wall* wall: _walls) {
        wall->paint(painter);
    }
}

QList<QPair<QPoint, SegmentRotation>> Level::getNeighbours(const QPoint& pnt, SegmentRotation rot) const {
    QList<QPair<QPoint, SegmentRotation>> list;
    QHash<SegmentRotation, QPoint> deltas = {
            {SegmentRotation::NONE,   {-1, 0}},
            {SegmentRotation::CW_90,  {0, -1}},
            {SegmentRotation::CW_180, {1, 0}},
            {SegmentRotation::CW_270, {0, 1}},
    };
    for (SegmentRotation deltaRot : {SegmentRotation::CW_90, SegmentRotation::NONE, SegmentRotation::CW_270}) {
        deltaRot = combine(deltaRot, rot);
        QPoint delta = deltas[deltaRot];
        QPoint point = pnt + delta;
        if (!getWallAt(point)){
            list.append({point, deltaRot});
        }
    }
    return list;
}

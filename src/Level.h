#pragma once

#include <QList>
#include <QRect>
#include <QPoint>
#include "Snek.h"

class QPainter;
class Wall;

class Level {
private:
    QList<Wall*> _walls;
    Wall* borderWall;
    QRect rect;

public:
    explicit Level(const QRect& rect);
    ~Level();
    Level(const Level&) = delete;
    Level& operator=(const Level&) = delete;

    Wall* getWallAt(const QPoint& pos) const;

    void removeOneWall(Wall* wall);

    void appendWall(Wall* wall);

    void paint(QPainter& painter) const;

    QList<QPair<QPoint, SegmentRotation>> getNeighbours(const QPoint& pnt, SegmentRotation rot) const;
};

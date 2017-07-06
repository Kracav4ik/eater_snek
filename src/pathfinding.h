#pragma once

#include <QList>
#include <QPoint>
#include "Snek.h"

class Appal;
class Level;

enum class Commands{
    FORWARD,
    LEFT,
    RIGHT,
    GROW_UP,
    SHRINK,
};

typedef QPair<QPoint, SegmentRotation> PathPoint;
typedef QList<PathPoint> Path;

QList<Commands> fromPointToCommand(Path list, PathPoint snek);
Path toNearestAppal(const QPoint& headPos, SegmentRotation headRot, const QList<Appal*>& appals, const Level& level);

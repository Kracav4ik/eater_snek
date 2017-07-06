#pragma once

#include <QList>
#include <QPoint>
#include "snek_enums.h"

class AbstractAppalStore;
class AbstractLevel;

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
Path toNearestAppal(const QPoint& headPos, SegmentRotation headRot, const AbstractAppalStore& appals, const AbstractLevel& level);

#pragma once

#include "snek_enums.h"

class AbstractLevel {
public:
    virtual QList<QPair<QPoint, SegmentRotation>> getNeighbours(const QPoint& pnt, SegmentRotation rot) const = 0;

    virtual ~AbstractLevel() = default;
};

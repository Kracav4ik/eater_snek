#pragma once

#include <QPoint>

enum class SegmentRotation {
    NONE,
    CW_90,
    CW_180,
    CW_270,
};
SegmentRotation invert(SegmentRotation rot);
QPoint rotatePoint(const QPoint& point, const QPoint& center, SegmentRotation rotation);
SegmentRotation combine(SegmentRotation r1, SegmentRotation r2);
int qHash(const SegmentRotation& p);

enum class SegmentType{
    HEAD,
    BODY,
    RIGHT,
    LEFT,
    TAIL
};
SegmentRotation rotate(SegmentRotation rotation, SegmentType direction);

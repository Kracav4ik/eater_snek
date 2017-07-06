#include "snek_enums.h"

SegmentRotation rotateLeft(SegmentRotation rotation){
    return SegmentRotation((static_cast<int>(rotation) + 3) % 4);
}

SegmentRotation rotateRight(SegmentRotation rotation){
    return SegmentRotation((static_cast<int>(rotation) + 1) % 4);
}

SegmentRotation combine(SegmentRotation r1, SegmentRotation r2) {
    switch (r1) {
        case SegmentRotation::NONE:
            return r2;
        case SegmentRotation::CW_90:
            return rotateRight(r2);
        case SegmentRotation::CW_180:
            return invert(r2);
        case SegmentRotation::CW_270:
            return rotateLeft(r2);
    }
}

int qHash(const SegmentRotation& p) {
    return static_cast<int>(p);
}

SegmentRotation rotate(SegmentRotation rotation, SegmentType direction) {
    if (direction == SegmentType::LEFT){
        return rotateLeft(rotation);
    } else if (direction == SegmentType::RIGHT) {
        return rotateRight(rotation);
    }
    return rotation;
}

SegmentRotation invert(SegmentRotation rot) {
    if (rot == SegmentRotation::CW_90) {
        return SegmentRotation::CW_270;
    }
    if (rot == SegmentRotation::CW_270) {
        return SegmentRotation::CW_90;
    }
    return rot;
}

QPoint rotatePoint(const QPoint& point, const QPoint& center, SegmentRotation rotation) {
    QPoint result = point - center;
    if (rotation == SegmentRotation::CW_90) {
        result = QPoint(-result.y(), result.x());
    }
    else if (rotation == SegmentRotation::CW_180) {
        result = QPoint(-result.x(), -result.y());
    }
    else if (rotation == SegmentRotation::CW_270) {
        result = QPoint(result.y(), -result.x());
    }
    return result + center;
}

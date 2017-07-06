#include "gtest/gtest.h"

#include "pathfinding.h"
#include "AbstractLevel.h"
#include "AbstractAppalStore.h"

class TestLevel : public AbstractLevel, public AbstractAppalStore {
public:
    QList<QPair<QPoint, SegmentRotation>> getNeighbours(const QPoint& pnt, SegmentRotation rot) const override {
        return {};
    }

    QList<QPoint> getAllAppalsPos() const override {
        return {};
    }
};

TEST(pathfinding, bfs) {
    TestLevel level;
    ASSERT_EQ(Path(), toNearestAppal({}, SegmentRotation::NONE, level, level));
}

#include "gtest/gtest.h"

#include "pathfinding.h"
#include "AbstractLevel.h"
#include "AbstractAppalStore.h"

#include <QRect>
#include <QHash>


class TestLevel : public AbstractLevel, public AbstractAppalStore {
private:
    QList<QPoint> appals;
    QList<QPoint> walls;
    QPoint bigA;
    QRect rect;
    PathPoint head = {{-1, -1}, SegmentRotation::NONE};
    Path path;

public:
    explicit TestLevel(const QString& level);

    bool getWallAt(QPoint pos) const;

    QList<QPair<QPoint, SegmentRotation>> getNeighbours(const QPoint& pnt, SegmentRotation rot) const override {
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
            if (getWallAt(point)) {
                list.append({point, deltaRot});
            }
        }
        return list;
    }

    QList<QPoint> getAllAppalsPos() const override {
        return appals;
    }

    QPoint getHeadPos() const {
        return head.first;
    }

    SegmentRotation getHeadRot() const {
        return head.second;
    }

    Path getExpectedPath() const {
        return path;
    }
};

TestLevel::TestLevel(const QString& level) {
    if (level.isEmpty()) {
        head.first = {0, 0};
        return;
    }
    QList<QPoint> prePath;
    const QString& string = level.section("\n", 1, 1);
    int width = string.size();
    int height = level.size() / width;
    rect = {{0, 0}, QSize(width, height)};
    for (int y = 0; y < height; ++y) {
        int x = 0;
        QString cur = level.section("\n", y + 1, y + 1);
        for (QChar c : cur) {
            QPoint curPos(x, y);
            x++;
            if (c == 'A') {
                bigA = curPos;
                appals.append(curPos);
            } else if (c == 'a') {
                appals.append(curPos);
            } else if (c == 'S'){
                head.first = curPos;
            } else if (c == 's' && head.first != QPoint(-1, -1)) {
                const QPoint& dpoint = head.first - curPos;
                if (dpoint.manhattanLength() == 1) {
                    if (dpoint.x() == 1) {
                        head.second = SegmentRotation::CW_180;
                    } else if (dpoint.y() == 1) {
                        head.second = SegmentRotation::CW_270;
                    } else if (dpoint.y() == -1) {
                        head.second = SegmentRotation::CW_90;
                    }
                }
            } else if (c == '+') {
                prePath.append(curPos);
            } else if (c == '#') {
                walls.append(curPos);
            }

        }
    }
    PathPoint pathSegment = head;
    path.append(head);
    while (true) {
        QList<QPair<QPoint, SegmentRotation>> neighbours = getNeighbours(pathSegment.first, pathSegment.second);
        if (neighbours.empty()) {
            break;
        }
        for (PathPoint neighbour : neighbours) {
            QPoint& first = neighbour.first;
            if (prePath.contains(first) && !path.contains(neighbour)) {
                path.append(neighbour);
                pathSegment = neighbour;
                break;
            }
            if (bigA == first) {
                path.append({bigA, neighbour.second});
                return;
            }
        }
    }
}

inline bool TestLevel::getWallAt(QPoint pos) const {
    return rect.contains(pos) && !walls.contains(pos);
}

void checkForLevel(const char* levelData) {
    TestLevel level(levelData);
    ASSERT_EQ(level.getExpectedPath(), toNearestAppal(level.getHeadPos(), level.getHeadRot(), level, level));
}

TEST(basic, parse) {
    TestLevel level(R"(
##########
#   A++  #
#a    +  #
#     +  #
#     Sss#
##########
)");

    ASSERT_EQ(SegmentRotation::NONE, level.getHeadRot());
    ASSERT_EQ(QPoint(6, 4), level.getHeadPos());
    ASSERT_EQ(QList<QPoint>({{4, 1}, {1, 2}}), level.getAllAppalsPos());
    ASSERT_EQ(Path({
            {{6, 4}, SegmentRotation::NONE},
            {{6, 3}, SegmentRotation::CW_90},
            {{6, 2}, SegmentRotation::CW_90},
            {{6, 1}, SegmentRotation::CW_90},
            {{5, 1}, SegmentRotation::NONE},
            {{4, 1}, SegmentRotation::NONE},
    }), level.getExpectedPath());
}

TEST(pathfinding, bfs) {
    checkForLevel("");
    checkForLevel(R"(
##########
#   A++  #
#a    +  #
#     +  #
#     Sss#
##########
)");
    checkForLevel(R"(
##########
#   A++  #
#a####+  #
##   ++  #
#    Ssss#
##########
)");
}

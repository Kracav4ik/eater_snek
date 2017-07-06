#include "pathfinding.h"

#include "Appal.h"
#include "Level.h"

int qHash(const QPoint& p){
    return qHash(p.x()) + 31*qHash(p.y());
}

QList<Commands> fromPointToCommand(Path list, PathPoint snek) {
    QList<Commands> res;
    QPoint headPos = snek.first;
    SegmentRotation rot = snek.second;
    for (PathPoint pos : list) {
        QPoint appalPos = rotatePoint(pos.first, headPos, invert(rot));
        int dX = headPos.x() - appalPos.x();
        int dY = headPos.y() - appalPos.y();
        if (dY == 0){
            if (dX > 0) {
                res.append(Commands::FORWARD);
            }
            continue;
        } else if (dY > 0) {
            res.append(Commands::RIGHT);
        } else {
            res.append(Commands::LEFT);
        }
        headPos = pos.first;
        rot = pos.second;
    }
    return res;
}

Path toNearestAppal(const QPoint& headPos, SegmentRotation headRot, const QList<Appal*>& appals, const Level& level) {
    Path black;
    Path grey = {{headPos, headRot}};
    Path newGrey;
    QHash<QPoint, PathPoint> p2p;

    int i = 0;

    while (!grey.empty()) {
        for (auto&& pathPoint : grey) {
            for (auto&& neighbour : level.getNeighbours(pathPoint.first, pathPoint.second)) {
                if (grey.contains(neighbour) || black.contains(neighbour) || newGrey.contains(neighbour) || p2p.contains(neighbour.first)) {
                    continue;
                }
                newGrey.append(neighbour);
                p2p[neighbour.first] = pathPoint;
                for (const Appal* appal : appals) {
                    if (appal->getPos() == neighbour.first){
                        QPoint last = neighbour.first;
                        Path way;
                        way.prepend(neighbour);
                        while (p2p.contains(last) && last != headPos){
                            i++;
                            way.prepend(p2p[last]);
                            last = p2p[last].first;
                        }
                        return way;
                    }
                }
            }
        }
        black.append(grey);
                grey = newGrey;
        newGrey.clear();
    }
    return {};
};

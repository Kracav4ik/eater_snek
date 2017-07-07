#include "SnekCommands.h"
#include "params.h"

int qHash(Commands p);
QPoint nextPos(const QPoint& pos, SegmentRotation rot);
void SnekCommands::paint(QPainter& p) const {
    QList<Commands> newCmds;
    for (Commands command : commands) {
        if (command == Commands::SHRINK) {
            continue;
        }
        newCmds.append(command);
    }
    if (newCmds.isEmpty()) {
        return;
    }
    static const QHash<Commands, SegmentRotation> commands2rot = {
            {Commands::FORWARD, SegmentRotation::NONE},
            {Commands::LEFT, SegmentRotation::CW_270},
            {Commands::RIGHT, SegmentRotation::CW_90},
            {Commands::GROW_UP, SegmentRotation::NONE},
    };

    QPoint point = snek->getHeadPos();
    SegmentRotation rot = snek->getHeadRotation();

    p.save();

    QPen pen = p.pen();
    pen.setWidthF(1.f / GRID_SIZE);
    pen.setColor(Qt::magenta);
    p.setPen(pen);
    p.translate(.5f, .5f);
    QPolygon polygon;
    for (Commands command : newCmds) {
        rot = combine(commands2rot[command], rot);
        const QPoint& pos = nextPos(point, rot);
        polygon.append(pos);
        point = pos;
    }
    p.drawPolyline(polygon);
    p.drawEllipse((QPointF)polygon.last(), .4f, .4f);

    p.restore();
}

bool SnekCommands::isEmpty() const {
    return commands.isEmpty();
}

void SnekCommands::append(Commands cmd) {
    commands.append(cmd);
}

Commands SnekCommands::takeFirst() {
    return commands.takeFirst();
}

void SnekCommands::setSnek(const Snek& s) {
    snek = &s;
}

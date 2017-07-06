#pragma once

#include <QObject>
#include <QImage>
#include "snek_enums.h"

class QPainter;
class SnekSegment;

class Snek : public QObject {
Q_OBJECT
private:
    QList<SnekSegment*> segments;
    QImage img;

    void paintSegment(const SnekSegment& segment, QPainter& p) const;

public:
    void paint(QPainter& p) const;
    QList<QPoint> getSegmentsPoints() const;

    QPoint getHeadNextPos(SegmentType direction) const;
    const QPoint& getHeadPos() const;
    SegmentRotation getHeadRotation() const;

    Snek();
    ~Snek() override;
    Snek(const Snek&) = delete;
    Snek& operator=(const Snek&) = delete;

    void shrinkBody();
    void addHead(SegmentType direction);
};

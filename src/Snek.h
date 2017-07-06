#pragma once

#include <QObject>
#include <QImage>
#include <QPoint>

class QPainter;
class SnekSegment;

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

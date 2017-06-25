#pragma once

#include <QObject>
#include <QImage>

class QPainter;
class SnekSegment;

enum class SegmentRotation {
    NONE,
    CW_90,
    CW_180,
    CW_270,
};
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

    void addHead(SegmentType direction);

public:
    void paint(QPainter& p) const;

    const QPoint& getHeadPos();
    SegmentRotation getHeadRotation();

    Snek();
    ~Snek() override;
    Snek(const Snek&) = delete;
    Snek& operator=(const Snek&) = delete;

    void moveForward();

    void moveLeft();

    void moveRight();

    void growUp();

    void shrinkBody();
};

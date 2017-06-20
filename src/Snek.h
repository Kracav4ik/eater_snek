#pragma once

#include <QObject>
#include <QImage>

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

    Snek();
    virtual ~Snek();
};

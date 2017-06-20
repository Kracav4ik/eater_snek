#pragma once

#include <QObject>

class QPainter;

class Snek : public QObject {
Q_OBJECT
public:
    void paint(QPainter& p) const;
};

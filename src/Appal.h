#pragma once

#include <QObject>
#include <QPoint>

class QPainter;

class Appal: public QObject {
Q_OBJECT
private:
    QPoint pos;

public:
    void paint(QPainter& p) const;

    explicit Appal(const QPoint& pos);

    Appal(const Appal&) = delete;
    Appal& operator=(const Appal&) = delete;

    const QPoint& getPos() const;
};

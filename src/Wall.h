#pragma once

#include <QPoint>
#include <QPainter>


class Wall {
private:
    QPoint position;

public:
    explicit Wall(const QPoint& position);

    Wall(const Wall&) = delete;
    Wall& operator=(const Wall&) = delete;


    const QPoint& getPos() const;

    void paint(QPainter& p) const;
};



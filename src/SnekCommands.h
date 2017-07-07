#pragma once


#include <QPainter>
#include "pathfinding.h"
#include "Snek.h"

class SnekCommands {
private:
    QList<Commands> commands;
    const Snek* snek  = nullptr;
public:
    void paint(QPainter& p) const;

    bool isEmpty() const;

    void append(Commands commands);

    Commands takeFirst();

    void setSnek(const Snek& s);
};

#include "Snek.h"

#include "params.h"
#include <QPainter>

void Snek::paint(QPainter& p) const {
    p.fillRect(GRID_SIZE, 2*GRID_SIZE, 5*GRID_SIZE, 3*GRID_SIZE, Qt::magenta);
    p.drawText(2*GRID_SIZE, 4*GRID_SIZE, "S N E K");
}

#include "CanvasWidget.h"

#include "params.h"
#include "Snek.h"
#include <QPainter>

void CanvasWidget::paintEvent(QPaintEvent* event) {
    QImage pattern(GRID_SIZE, GRID_SIZE, QImage::Format_RGB32);
    QPainter localP(&pattern);
    localP.fillRect(rect(), QColor(255, 255, 255));
    localP.drawLines(QVector<QPoint>{
            QPoint(0, 0), QPoint(0, GRID_SIZE),
            QPoint(0, 0), QPoint(GRID_SIZE, 0),
    });
    QBrush b(pattern);
    QPainter p(this);

    p.scale(4, 4);

    p.fillRect(rect(), b);

    if (snek){
        snek->paint(p);
    }
}

void CanvasWidget::setSnek(const Snek& s) {
    snek = &s;
}

CanvasWidget::CanvasWidget(QWidget* parent): QWidget(parent) {}

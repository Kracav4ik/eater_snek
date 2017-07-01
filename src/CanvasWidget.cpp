#include "CanvasWidget.h"

#include <QPainter>
#include <QMouseEvent>

#include "params.h"
#include "Snek.h"
#include "Appal.h"
#include "Wall.h"

int pixelToGrid(int pixelPos) {
    return pixelPos/GRID_SIZE/SCALE;
}

void CanvasWidget::paintEvent(QPaintEvent* event) {
    QImage pattern(GRID_SIZE_2D, QImage::Format_RGB32);
    QPainter localP(&pattern);
    localP.fillRect(rect(), QColor(255, 255, 255));
    localP.drawLines(QVector<QPoint>{
            QPoint(0, 0), QPoint(0, GRID_SIZE),
            QPoint(0, 0), QPoint(GRID_SIZE, 0),
    });
    QBrush b(pattern);
    QPainter p(this);

    p.scale(SCALE, SCALE);

    p.fillRect(rect(), b);

    if (snek){
        snek->paint(p);
    }
    if (appals) {
        for (const Appal* appal: *appals) {
            appal->paint(p);
        }
    }
    if (walls) {
        for (const Wall* wall: *walls) {
            wall->paint(p);
        }
    }
}

void CanvasWidget::setSnek(const Snek& s) {
    snek = &s;
}

CanvasWidget::CanvasWidget(QWidget* parent): QWidget(parent) {}

void CanvasWidget::setAppals(const QList<Appal*>& apps) {
    appals = &apps;
}

void CanvasWidget::mousePressEvent(QMouseEvent* event) {
    Qt::MouseButton button = event->button();
    bool isLeftButton;
    if(button == Qt::LeftButton){
        isLeftButton = true;
    } else if(button == Qt::RightButton){
        isLeftButton = false;
    } else {
        return;
    }

    int x = pixelToGrid(event->x());
    int y = pixelToGrid(event->y());
    emit gridClicked(QPoint(x, y), isLeftButton);
}

void CanvasWidget::setWalls(const QList<Wall*>& wlls) {
    walls = &wlls;
}

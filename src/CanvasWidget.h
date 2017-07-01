#pragma once

#include <QWidget>
#include <QList>

class Snek;
class QPaintEvent;
class Appal;
class Wall;

class CanvasWidget : public QWidget {
Q_OBJECT
private:
    const Snek* snek = nullptr;
    const QList<Appal*>* appals = nullptr;
    const QList<Wall*>* walls = nullptr;

public:
    void setSnek(const Snek& s);
    void setAppals(const QList<Appal*>& apps);
    void setWalls(const QList<Wall*>& list);

    explicit CanvasWidget(QWidget* parent);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void gridClicked(const QPoint& pos, bool isLeftButton);
};

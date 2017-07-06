#pragma once

#include <QWidget>
#include <QList>
#include "Level.h"

class Snek;
class QPaintEvent;
class Appal;
class Level;

class CanvasWidget : public QWidget {
Q_OBJECT
private:
    const Snek* snek = nullptr;
    const QList<Appal*>* appals = nullptr;
    const Level* level = nullptr;

public:
    void setSnek(const Snek& s);
    void setAppals(const QList<Appal*>& apps);
    void setLevel(const Level& lvl);

    explicit CanvasWidget(QWidget* parent);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void gridClicked(const QPoint& pos, bool isLeftButton);
};

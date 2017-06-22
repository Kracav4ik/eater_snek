#pragma once

#include <QWidget>
#include <QList>

class Snek;
class QPaintEvent;
class Appal;

class CanvasWidget : public QWidget {
Q_OBJECT
private:
    const Snek* snek = nullptr;
    const QList<Appal*>* appals = nullptr;

public:
    void setSnek(const Snek& s);
    void setAppals(const QList<Appal*>& apps);

    explicit CanvasWidget(QWidget* parent);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void gridClicked(const QPoint& pos);
};

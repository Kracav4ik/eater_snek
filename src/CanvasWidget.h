#pragma once

#include <QWidget>

class Snek;
class QPaintEvent;

class CanvasWidget : public QWidget {
Q_OBJECT
private:
    const Snek* snek = nullptr;

public:
    void setSnek(const Snek& s);

    explicit CanvasWidget(QWidget* parent);

protected:
    void paintEvent(QPaintEvent* event) override;
};

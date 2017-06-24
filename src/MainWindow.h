#pragma once

#include "Snek.h"

#include <QMainWindow>
#include <QList>
#include <QTimer>

#include "ui_eater_snek.h"

enum class Commands{
    FORWARD,
    LEFT,
    RIGHT,
    GROW_UP,
    SHRINK,
};

class Appal;

class MainWindow : public QMainWindow, private Ui::MainWindow {
Q_OBJECT
private:
    Snek snek;
    QList<Appal*> appals;
    QList<Commands> commands;
    QTimer timer;

private slots:
    void on_canvas_gridClicked(const QPoint& pos);
    void processQueue();
    void on_delay_valueChanged(int i);

public:
    MainWindow();
    ~MainWindow() override;

protected:
    void keyPressEvent(QKeyEvent* event) override;
};


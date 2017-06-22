#pragma once

#include "Snek.h"

#include <QMainWindow>
#include <QList>

#include "ui_eater_snek.h"

class Appal;

class MainWindow : public QMainWindow, private Ui::MainWindow {
Q_OBJECT
private:
    Snek snek;
    QList<Appal*> appals;

private slots:
    void on_canvas_gridClicked(const QPoint& pos);

public:
    MainWindow();
    ~MainWindow() override;

protected:
    void keyPressEvent(QKeyEvent* event) override;
};


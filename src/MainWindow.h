#pragma once

#include "Snek.h"

#include <QMainWindow>

#include "ui_eater_snek.h"


class MainWindow : public QMainWindow, private Ui::MainWindow {
Q_OBJECT
private:
    Snek snek;

public:
    MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event) override;
};


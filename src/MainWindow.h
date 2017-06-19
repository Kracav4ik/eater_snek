#pragma once

#include <QMainWindow>

#include "ui_eater_snek.h"


class MainWindow : public QMainWindow, private Ui::MainWindow {
Q_OBJECT
private:

public:
    MainWindow();
};


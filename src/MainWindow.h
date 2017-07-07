#pragma once

#include <QMainWindow>
#include <QList>
#include <QTimer>
#include <QHash>

#include "ui_eater_snek.h"
#include "Snek.h"
#include "Level.h"
#include "pathfinding.h"
#include "SnekCommands.h"


class Appal;
class Wall;

class MainWindow : public QMainWindow, private Ui::MainWindow {
Q_OBJECT
private:
    Snek snek;
    QList<Appal*> appals;
    Level level;
    SnekCommands commands;
    QHash<int, Commands> keybind;
    QTimer timer;

    void toAppal();

    void appendCommand(Commands cmd);

private slots:
    void on_canvas_gridClicked(const QPoint& pos, bool isLeftButton);
    void processQueue();
    void on_delay_valueChanged(int i);

public:
    MainWindow();
    ~MainWindow() override;

protected:
    void keyPressEvent(QKeyEvent* event) override;
};


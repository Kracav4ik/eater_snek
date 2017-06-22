#include "MainWindow.h"

#include "Appal.h"
#include <QKeyEvent>

MainWindow::MainWindow() {
    setupUi(this);

    canvas->setSnek(snek);
    canvas->setAppals(appals);

    show();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    switch (event->key()){
        case Qt::Key_W:
            snek.moveForward();
            break;
        case Qt::Key_A:
            snek.moveLeft();
            break;
        case Qt::Key_D:
            snek.moveRight();
            break;
        case Qt::Key_Space:
            snek.growUp();
            break;
    }
    canvas->update();
}

void MainWindow::on_canvas_gridClicked(const QPoint& pos) {
    for (Appal* appal: appals) {
        if (pos == appal->getPos()){
            return;
        }
    }
    appals.append(new Appal(pos));
    canvas->update();
}

MainWindow::~MainWindow() {
    for (Appal* appal : appals) {
        delete appal;
    }
}

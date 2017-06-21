#include "MainWindow.h"
#include <QKeyEvent>

MainWindow::MainWindow() {
    setupUi(this);

    canvas->setSnek(snek);

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
#include "MainWindow.h"

MainWindow::MainWindow() {
    setupUi(this);

    canvas->setSnek(snek);

    show();
}

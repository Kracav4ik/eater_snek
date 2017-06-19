#include <QApplication>
#include <QTime>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    qsrand((uint) QTime::currentTime().msecsSinceStartOfDay());
    QApplication app(argc, argv);
    MainWindow* window = new MainWindow();
    return app.exec();
}
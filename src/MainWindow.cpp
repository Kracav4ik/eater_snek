#include "MainWindow.h"

#include "Appal.h"
#include <QKeyEvent>

MainWindow::MainWindow(): timer(this) {
    setupUi(this);

    connect(&timer, SIGNAL(timeout()), this, SLOT(processQueue()));
    timer.start(delay->value());

    canvas->setSnek(snek);
    canvas->setAppals(appals);

    show();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    switch (event->key()){
        case Qt::Key_W:
            commandsWidget->setText(commandsWidget->text() + "W ");
            commands.append(Commands::FORWARD);
            break;
        case Qt::Key_A:
            commandsWidget->setText(commandsWidget->text() + "A ");
            commands.append(Commands::LEFT);
            break;
        case Qt::Key_D:
            commandsWidget->setText(commandsWidget->text() + "D ");
            commands.append(Commands::RIGHT);
            break;
        case Qt::Key_Space:
            commandsWidget->setText(commandsWidget->text() + u8"｢｣ ");
            commands.append(Commands::GROW_UP);
            break;
        case Qt::Key_S:
            commandsWidget->setText(commandsWidget->text() + "S ");
            commands.append(Commands::SHRINK);
            break;
        default:
            return;
    }
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

void MainWindow::processQueue() {
    if (commands.isEmpty()){
        return;
    }
    commandsWidget->setText(commandsWidget->text().section(' ', 1));

    bool shrink = true;
    switch (commands.first()){
        case Commands::FORWARD:
            snek.moveForward();
            break;
        case Commands::LEFT:
            snek.moveLeft();
            break;
        case Commands::RIGHT:
            snek.moveRight();
            break;
        case Commands::GROW_UP:
            snek.growUp();
            shrink = false;
            break;
        case Commands::SHRINK:
            snek.shrinkBody();
            shrink = false;
            break;
    }
    for (Appal* appal: appals) {
        if (snek.getHeadPos() == appal->getPos()){
            appals.removeOne(appal);
            shrink = false;
        }
    }
    if (shrink){
        snek.shrinkBody();
    }
    commands.removeFirst();
    canvas->update();
}

void MainWindow::on_delay_valueChanged(int i) {
    timer.setInterval(i);
}

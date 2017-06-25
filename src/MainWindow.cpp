#include "MainWindow.h"

#include "Appal.h"
#include <QKeyEvent>

MainWindow::MainWindow():
        timer(this),
        keybind({
                {Qt::Key_W,     Commands::FORWARD},
                {Qt::Key_A,     Commands::LEFT},
                {Qt::Key_D,     Commands::RIGHT},
                {Qt::Key_Space, Commands::GROW_UP},
                {Qt::Key_S,     Commands::SHRINK},
        })
{
    setupUi(this);

    connect(&timer, SIGNAL(timeout()), this, SLOT(processQueue()));
    timer.start(delay->value());

    canvas->setSnek(snek);
    canvas->setAppals(appals);

    show();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (keybind.contains(event->key())) {
        appendCommand(keybind[event->key()]);
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
        if (!appals.isEmpty()){
            toAppal(appals.first()->getPos());
        }
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

void MainWindow::toAppal(const QPoint& pos) {
    QPoint appalPos = rotatePoint(pos, snek.getHeadPos(), invert(snek.getHeadRotation()));
    int dX = snek.getHeadPos().x() - appalPos.x();
    int dY = snek.getHeadPos().y() - appalPos.y();
    bool left = dX > 0;
    bool up = dY > 0;
    dX = abs(dX);
    dY = abs(dY);
    if (dY == 0){
        left ? forwardTo(dX) : turnRight();
        return;
    }
    equal(!up, dY);
}

void MainWindow::equal(bool rot, int count) {
    if (count == 0){
        return;
    }
    rot? turnLeft(): turnRight();

    forwardTo(count - 1);
}

void MainWindow::turnLeft() {
    appendCommand(Commands::LEFT);
}

void MainWindow::turnRight() {
    appendCommand(Commands::RIGHT);
}

void MainWindow::forwardTo(int count) {
    for (int i = 0; i < count; ++i){
        appendCommand(Commands::FORWARD);
    }
}

const char* const CMD_TEXT[] = {
        "W ",       // FORWARD
        "A ",       // LEFT
        "D ",       // RIGHT
        u8"｢｣ ",    // GROW_UP
        "S ",       // SHRINK
};

void MainWindow::appendCommand(Commands cmd) {
    commandsWidget->setText(commandsWidget->text() + CMD_TEXT[static_cast<int>(cmd)]);
    commands.append(cmd);
}

#include "MainWindow.h"

#include "Appal.h"
#include "Wall.h"
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
    canvas->setWalls(walls);

    show();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (keybind.contains(event->key())) {
        appendCommand(keybind[event->key()]);
    }
}

void MainWindow::on_canvas_gridClicked(const QPoint& pos, bool isLeftButton) {
    if (isLeftButton) {
        for (Appal* appal: appals) {
            if (pos == appal->getPos()){
                return;
            }
        }
        appals.append(new Appal(pos));
    } else {
        Wall* existingWall = nullptr;
        for (Wall* wall: walls) {
            if (pos == wall->getPos()){
                existingWall = wall;
                break;
            }
        }
        if (existingWall) {
            walls.removeOne(existingWall);
            delete existingWall;
        }
        else {
            walls.append(new Wall(pos));
        }
    }
    canvas->update();
}

MainWindow::~MainWindow() {
    for (Appal* appal : appals) {
        delete appal;
    }
    for (Wall* wall : walls) {
        delete wall;
    }
}

int distance(const QPoint& p1, const QPoint& p2) {
    return (p1 - p2).manhattanLength();
}

int qHash(Commands c){
    return qHash(static_cast<int>(c));
}

void MainWindow::processQueue() {
    if (commands.isEmpty()){
        if (appals.isEmpty()){
            return;
        }
        QPoint minPoint = appals.first()->getPos();
        int minLength = distance(minPoint, snek.getHeadPos());
        for (Appal* appal: appals) {
            int length = distance(appal->getPos(), snek.getHeadPos());
            if (minLength > length) {
                minLength = length;
                minPoint = appal->getPos();
            }
        }
        toAppal(minPoint);
    }
    commandsWidget->setText(commandsWidget->text().section(' ', 1));

    Commands command = commands.takeFirst();

    static const QHash<Commands, SegmentType> commands2segments = {
            {Commands::FORWARD, SegmentType::BODY},
            {Commands::LEFT, SegmentType::LEFT},
            {Commands::RIGHT, SegmentType::RIGHT},
            {Commands::GROW_UP, SegmentType::BODY},
    };

    bool shrink = true;
    if (commands2segments.contains(command)){
        if (command == Commands::GROW_UP){
            shrink = false;
        }
        SegmentType direction = commands2segments[command];
        QPoint p = snek.getHeadNextPos(direction);
        for (Wall* wall : walls) {
            if (p == wall->getPos()) {
                return;
            }
        }
        snek.addHead(direction);
    } else if (command == Commands::SHRINK){
        snek.shrinkBody();
        shrink = false;
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
        if (left) {
            forwardTo(dX);
        } else {
            turnRight();
        }
        return;
    }
    equal(!up, dY);
}

void MainWindow::equal(bool rot, int count) {
    if (count == 0){
        return;
    }
    if (rot) {
        turnLeft();
    } else {
        turnRight();
    }

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

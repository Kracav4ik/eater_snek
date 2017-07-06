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
        }),
        level(QRect(2, 2, 10, 10))
{
    setupUi(this);

    connect(&timer, SIGNAL(timeout()), this, SLOT(processQueue()));
    timer.start(delay->value());

    canvas->setSnek(snek);
    canvas->setAppals(appals);
    canvas->setLevel(level);

    show();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (keybind.contains(event->key())) {
        appendCommand(keybind[event->key()]);
    }
}

void MainWindow::on_canvas_gridClicked(const QPoint& pos, bool isLeftButton) {
    for (Appal* appal: appals) {
        if (pos == appal->getPos()) {
            return;
        }
    }
    for (QPoint snekSegmentPos: snek.getSegmentsPoints()) {
        if (pos == snekSegmentPos) {
            return;
        }
    }

    if (isLeftButton) {
        if (level.getWallAt(pos)) {
            return;
        }
        appals.append(new Appal(pos));
    } else {
        Wall* existingWall = level.getWallAt(pos);
        if (existingWall) {
            level.removeOneWall(existingWall);
        }else {
            level.appendWall(new Wall(pos));
        }
    }
    canvas->update();
}

MainWindow::~MainWindow() {
    for (Appal* appal : appals) {
        delete appal;
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
        toAppal();
        if (commands.isEmpty()) {
            return;
        }
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
        if (level.getWallAt(snek.getHeadNextPos(direction))) {
            return;
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

void MainWindow::toAppal() {
    Path way = toNearestAppal(snek.getHeadPos(), snek.getHeadRotation(), appals, level);
    QList<Commands> cmds = fromPointToCommand(way, {snek.getHeadPos(), snek.getHeadRotation()});
    for (Commands command : cmds) {
        appendCommand(command);
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

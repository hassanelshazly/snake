#include "include/game.h"
#include "include/tcp.h"
#include <QApplication>

Game *w;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new Game();
    w->show();

    return a.exec();
}

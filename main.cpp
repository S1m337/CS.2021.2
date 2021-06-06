#include "Controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Controller c;
    c.StartGame();

    return a.exec();
}

#include "mainwindow.h"
#include "controller.h"
#
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    Controller c;
    c.setView(&m);
    m.setController(&c);
    m.show();
    return a.exec();
}

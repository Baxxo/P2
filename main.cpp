#include "mainwindow.h"
#include "controller.h"
#include "model.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    MainWindow v;

    Model *m = new Model();
    Controller *c = new Controller(nullptr, m);

    c->setView(&v);
    v.setController(c);
    v.show();

    return a.exec();
}

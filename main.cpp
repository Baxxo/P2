#include "controller.h"
#include "mainwindow.h"
#include "model.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow v;

  Model *m = new Model();
  Controller *c = new Controller(nullptr, m);

  c->setView(&v);
  v.setController(c);
  v.show();

  return a.exec();
}

#include "client.h"

Client::Client(QWidget *parent) : QMainWindow(parent)
{
  label = new QLabel("Ciao da Client");
  setCentralWidget(label);

  desktop = QApplication::desktop();

  resize(300,300);
  move((desktop->width()-300)/2,(desktop->height()-300)/2);

}

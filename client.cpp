#include "client.h"

Client::Client(QWidget *parent) : QMainWindow(parent)
{
  label = new QLabel("Ciao da Cliente");

  setCentralWidget(label);

  desktop = QApplication::desktop();

  resize(300,300);
}

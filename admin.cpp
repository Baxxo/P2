#include "admin.h"

Admin::Admin(QWidget *parent) : QMainWindow(parent)
{
  label = new QLabel("Ciao da Admin");

  setCentralWidget(label);

  desktop = QApplication::desktop();

  resize(300,300);
}

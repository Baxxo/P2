#include "mainwindow.h"
#include "controller.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), controller(nullptr)
{

  title = new QLabel("QTheater");

  adminBtn = new QPushButton("Admin");
  clientBtn = new QPushButton("Cliente");

  v_layout = new QVBoxLayout();
  v_layout->addWidget(title,Qt::AlignTop);

  buttonLayout = new QVBoxLayout();
  buttonLayout->addWidget(adminBtn,Qt::AlignCenter);
  buttonLayout->addWidget(clientBtn,Qt::AlignCenter);

  mainLayout = new QGridLayout();
  mainLayout->addLayout(v_layout,0,0,Qt::AlignCenter);
  mainLayout->addLayout(buttonLayout,1,0,Qt::AlignCenter);

  widget = new QWidget(this);
  widget->setLayout(mainLayout);

  setCentralWidget(widget);

  desktop = QApplication::desktop();

  resize(300,300);
  move((desktop->width()-300)/2,(desktop->height()-300)/2);

  setStyle();
}

void MainWindow::setController(Controller *c)
{
    controller=c;

    connect(adminBtn, SIGNAL(clicked()), controller, SLOT(openAdmin()));
    connect(clientBtn, SIGNAL(clicked()), controller, SLOT(openClient()));
}


void MainWindow::setStyle()
{
  QFile file(":/qss/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
}

/*Controller* MainWindow::getController()
{
    return controller;
}*/

MainWindow *MainWindow::getMainwindow()
{
    return this;
}

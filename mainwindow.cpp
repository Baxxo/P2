#include "mainwindow.h"
#include "controller.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), controller(nullptr)
{

  title = new QLabel("Setup");

  adminBtn = new QPushButton("Admin");
  clientBtn = new QPushButton("Cliente");

  chooseUtenti = new QPushButton("Scegli file json per utenti");
  chooseFamiglie = new QPushButton("Scegli file json per famiglie");
  chooseEntrata = new QPushButton("Scegli file json per entrata film");

  v_layout = new QVBoxLayout();
  v_layout->addWidget(title,Qt::AlignTop);

  buttonLayout = new QVBoxLayout();
  buttonLayout->addWidget(chooseUtenti,Qt::AlignCenter);
  buttonLayout->addWidget(chooseFamiglie,Qt::AlignCenter);
  buttonLayout->addWidget(chooseEntrata,Qt::AlignCenter);

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
    connect(chooseUtenti, SIGNAL(clicked()), controller, SLOT(readUtenti()));
}

void MainWindow::changeMenu()
{
  buttonLayout->removeWidget(chooseUtenti);
  delete chooseUtenti;
  buttonLayout->removeWidget(chooseFamiglie);
  delete chooseFamiglie;
  buttonLayout->removeWidget(chooseEntrata);
  delete chooseEntrata;

  buttonLayout->addWidget(adminBtn,Qt::AlignCenter);
  buttonLayout->addWidget(clientBtn,Qt::AlignCenter);
}


void MainWindow::setStyle()
{
  QFile file(":/qss/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
}

MainWindow *MainWindow::getMainwindow()
{
    return this;
}

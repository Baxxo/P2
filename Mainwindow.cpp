#include "Mainwindow.h"

MainWindow::MainWindow(QWidget *parent, bool isOpAd, bool isOpCl)
  : QMainWindow(parent), isOpenAdmin(isOpAd), isOpenClient(isOpCl)
{
  admin = nullptr;
  client = nullptr;

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

  connect(adminBtn,SIGNAL(clicked()),this,SLOT(openAdmin()));
  connect(clientBtn,SIGNAL(clicked()),this,SLOT(openClient()));
}

void MainWindow::setStyle()
{
  QFile file(":/qss/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
}

void MainWindow::openAdmin()
{
  adminBtn->setEnabled(false);
  adminBtn->repaint();
  if (!admin) {
      admin = new Admin();
      admin->show();
    }else{
      admin->show();
    }
  adminBtn->setEnabled(true);
}

void MainWindow::openClient()
{
  clientBtn->setEnabled(false);
  clientBtn->repaint();
  if (!client) {
      client = new Client();
      client->show();
    }else{
      client->show();
    }
  clientBtn->setEnabled(true);
}

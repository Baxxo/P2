#include "mainwindow.h"
#include "controller.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), controller(nullptr), isVisReadBtn(true)
{

  changeBtn = new QPushButton(QIcon(":/images/reverse.png"),"");
  changeBtn->setFixedWidth(50);

  title = new QLabel("Setup");

  v_layout = new QVBoxLayout();
  v_layout->addWidget(title,Qt::AlignTop);

  buttonLayout = new QVBoxLayout();

  mainLayout = new QGridLayout();
  mainLayout->addWidget(changeBtn,0,0,Qt::AlignRight);
  mainLayout->addLayout(v_layout,1,0,Qt::AlignCenter);
  mainLayout->addLayout(buttonLayout,2,0,Qt::AlignCenter);

  widget = new QWidget(this);
  widget->setLayout(mainLayout);

  setCentralWidget(widget);

  desktop = QApplication::desktop();

  resize(300,300);
  move((desktop->width()-300)/2,(desktop->height()-300)/2);

  setStyle();

  prevAdmin = "Admin";

}

void MainWindow::setController(Controller *c)
{
    controller=c;
    connect(changeBtn, SIGNAL(clicked()), this,SLOT(changeMenuSlot()));

    createLayoutSetup();
}

void MainWindow::changeTitleAdmin(QString s)
{
  adminBtn->setText(s);
}

void MainWindow::setIsAdmin(bool b)
{
  controller->setIsAdmin(b);
}

void MainWindow::changeTitleChooseUtenti(QString s)
{
  chooseUtenti->setText(s);
}

void MainWindow::changeMenuSlot()
{
  changeMenu();
}

void MainWindow::changeMenu()
{
  if(isVisReadBtn){

      destroyLayoutSetup();
      createLayoutAdCl();
      title->setText("QTheater");

      isVisReadBtn = false;

    }else{

      destroyLayoutAdCl();
      createLayoutSetup();
      title->setText("Setup");

      isVisReadBtn = true;
    }
}

void MainWindow::createLayoutAdCl()
{
  adminBtn = new QPushButton(prevAdmin);
  clientBtn = new QPushButton("Cliente");

  buttonLayout->addWidget(adminBtn,Qt::AlignCenter);
  buttonLayout->addWidget(clientBtn,Qt::AlignCenter);

  connect(adminBtn, SIGNAL(clicked()), controller, SLOT(openAdmin()));
  connect(clientBtn, SIGNAL(clicked()), controller, SLOT(openClient()));


}

void MainWindow::destroyLayoutAdCl()
{
  prevAdmin = adminBtn->text();
  buttonLayout->removeWidget(adminBtn);
  buttonLayout->removeWidget(clientBtn);
  delete adminBtn;
  delete clientBtn;
}

void MainWindow::createLayoutSetup()
{
  chooseUtenti = new QPushButton("Scegli file json per utenti");
  chooseFamiglie = new QPushButton("Scegli file json per famiglie");
  chooseEntrata = new QPushButton("Scegli file json per entrata film");

  buttonLayout->addWidget(chooseUtenti,Qt::AlignCenter);
  buttonLayout->addWidget(chooseFamiglie,Qt::AlignCenter);
  buttonLayout->addWidget(chooseEntrata,Qt::AlignCenter);

  connect(chooseUtenti, SIGNAL(clicked()), controller, SLOT(readUtenti()));

}

void MainWindow::destroyLayoutSetup()
{
  buttonLayout->removeWidget(chooseUtenti);
  buttonLayout->removeWidget(chooseFamiglie);
  buttonLayout->removeWidget(chooseEntrata);
  delete chooseUtenti;
  delete chooseFamiglie;
  delete chooseEntrata;
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

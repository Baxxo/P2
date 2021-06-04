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

  buttonLayout = new QGridLayout();

  mainLayout = new QGridLayout();
  mainLayout->addWidget(changeBtn,0,0,Qt::AlignRight);
  mainLayout->addLayout(v_layout,1,0,Qt::AlignCenter);
  mainLayout->addLayout(buttonLayout,2,0,Qt::AlignCenter);

  pathUser = new QLabel("name json utenti");
  pathUser->setProperty("class", "path");

  pathFamilies = new QLabel("name json famiglie");
  pathFamilies->setProperty("class", "path");

  pathEntrata = new QLabel("name json archivio entrate/abbonamenti");
  pathEntrata->setProperty("class", "path");

  buttonLayout->addWidget(pathUser,0,1,Qt::AlignCenter);
  buttonLayout->addWidget(pathFamilies,1,1,Qt::AlignCenter);
  buttonLayout->addWidget(pathEntrata,2,1,Qt::AlignCenter);

  widget = new QWidget(this);
  widget->setLayout(mainLayout);

  setCentralWidget(widget);

  desktop = QApplication::desktop();

  resize(300,300);
  move((desktop->width()-300)/2,(desktop->height()-300)/2);

  setStyle();

  prevAdmin = "Admin";
  prevChooseUtenti = "Scegli file json per utenti";

}

void MainWindow::setController(Controller *c)
{
    controller=c;
    connect(changeBtn, SIGNAL(clicked()), this,SLOT(changeMenuSlot()));

    pathUser->setText(controller->getPathJsonUsers());
    pathFamilies->setText(controller->getPathJsonFamiglie());
    pathEntrata->setText(controller->getPathJsonEntrata());

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

void MainWindow::setLabelPathUser(QString s)
{
    pathUser->setText(s);
}

void MainWindow::setLabelPathFamiglie(QString s)
{
    pathFamilies->setText(s);
}

void MainWindow::setLabelPathEntrata(QString s)
{
    pathEntrata->setText(s);
}

void MainWindow::changeTitleChooseUtenti(QString s)
{
    prevChooseUtenti = s;
}

void MainWindow::changeTitleChooseFamiglie(QString s)
{
    prevChooseFamiglie = s;
}

void MainWindow::changeTitleChooseEntrata(QString s)
{
    prevChooseEntrata = s;
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

  buttonLayout->addWidget(adminBtn,0,0,Qt::AlignCenter);
  buttonLayout->addWidget(clientBtn,1,0,Qt::AlignCenter);

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
  chooseUtenti = new QPushButton(prevChooseUtenti);
  chooseFamiglie = new QPushButton("Scegli file json per famiglie");
  chooseEntrata = new QPushButton("Scegli file json per entrata film");

  buttonLayout->addWidget(chooseUtenti,0,0,Qt::AlignCenter);
  buttonLayout->addWidget(chooseFamiglie,1,0,Qt::AlignCenter);
  buttonLayout->addWidget(chooseEntrata,2,0,Qt::AlignCenter);

  connect(chooseUtenti, SIGNAL(clicked()), controller, SLOT(loadUsersinView()));

}

void MainWindow::destroyLayoutSetup()
{
    prevChooseUtenti = chooseUtenti->text();
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

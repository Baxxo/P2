#include "mainwindow.h"
#include "controller.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), controller(nullptr), isVisReadBtn(true)
{

  changeBtn = new QPushButton(QIcon(":/images/reverse.png"),"");
  changeBtn->setFixedWidth(50);

  title = new QLabel("Setup");  
  title->setProperty("class", "title");

  v_layout = new QVBoxLayout();
  v_layout->addWidget(title,Qt::AlignTop);

  buttonLayout = new QGridLayout();

  mainLayout = new QGridLayout();
  mainLayout->addWidget(changeBtn,0,0,Qt::AlignRight);
  mainLayout->addLayout(v_layout,1,0,Qt::AlignCenter);
  mainLayout->addLayout(buttonLayout,2,0,Qt::AlignCenter);

  pathUser = new QLabel("name json utenti");
  pathUser->setProperty("class", "path");
  pathUser->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

  pathFamilies = new QLabel("name json famiglie");
  pathFamilies->setProperty("class", "path");
  pathFamilies->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

  pathPosti= new QLabel("name json postiOccupati");
  pathPosti->setProperty("class", "path");
  pathPosti->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

  pathFilm= new QLabel("name json film");
  pathFilm->setProperty("class", "path");
  pathFilm->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

  pathEntrata = new QLabel("name json archivio entrate/abbonamenti");
  pathEntrata->setProperty("class", "path");
  pathEntrata->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

  buttonLayout->addWidget(pathUser,0,1,Qt::AlignCenter);
  buttonLayout->addWidget(pathFamilies,1,1,Qt::AlignCenter);
  buttonLayout->addWidget(pathEntrata,2,1,Qt::AlignCenter);
  buttonLayout->addWidget(pathPosti, 3, 1, Qt::AlignCenter);


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
    pathPosti->setText(controller->getPathJsonPosti());
    pathFilm->setText(controller->getPathJsonFilm());

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

void MainWindow::setLabelPathPosti(QString s)
{
    pathPosti->setText(s);
}

void MainWindow::setLabelPathFilm(QString s)
{
    pathFilm->setText(s);
}

void MainWindow::changeTitleChooseUtenti(QString s)
{
    prevChooseUtenti = s;
    if(chooseUtenti != nullptr) chooseUtenti->setText(s);
}

void MainWindow::changeTitleChooseFamiglie(QString s)
{
    prevChooseFamiglie = s;
    if(chooseFamiglie != nullptr) chooseFamiglie->setText(s);
}

void MainWindow::changeTitleChooseEntrata(QString s)
{
    prevChooseEntrata = s;
    if(chooseEntrata != nullptr) chooseEntrata->setText(s);
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
  adminBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

  clientBtn = new QPushButton("Cliente");
  clientBtn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

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
  adminBtn = nullptr;

  delete clientBtn;
  clientBtn = nullptr;
}

void MainWindow::createLayoutSetup()
{
  chooseUtenti = new QPushButton(prevChooseUtenti);
  chooseUtenti->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

  chooseFamiglie = new QPushButton("Scegli file json per famiglie");
  chooseFamiglie->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

  chooseEntrata = new QPushButton("Scegli file json per entrata film");
  chooseEntrata->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

  choosePosti= new QPushButton("Scegli file json per posti occupati");
  choosePosti->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

  chooseFilm=new QPushButton("Scegli json per film");
  chooseFilm->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

  buttonLayout->addWidget(chooseUtenti,0,0,Qt::AlignCenter);
  buttonLayout->addWidget(chooseFamiglie,1,0,Qt::AlignCenter);
  buttonLayout->addWidget(chooseEntrata,2,0,Qt::AlignCenter);
  buttonLayout->addWidget(choosePosti, 3, 0, Qt::AlignCenter);
  buttonLayout->addWidget(chooseFilm, 4, 0, Qt::AlignCenter);

  connect(chooseUtenti, SIGNAL(clicked()), controller, SLOT(loadUsersinView()));
  connect(chooseFamiglie, SIGNAL(clicked()), controller, SLOT(loadFamiliesinView()));
  connect(choosePosti, SIGNAL(clicked()), controller, SLOT(loadPostiOccupati()));
  connect(chooseFilm, SIGNAL(clicked()), controller, SLOT(loadFilm()));

}

void MainWindow::destroyLayoutSetup()
{
    prevChooseUtenti = chooseUtenti->text();
  buttonLayout->removeWidget(chooseUtenti);
  buttonLayout->removeWidget(chooseFamiglie);
  buttonLayout->removeWidget(chooseEntrata);
  buttonLayout->removeWidget(choosePosti);
  buttonLayout->removeWidget(chooseFilm);

  delete chooseUtenti;
  chooseUtenti = nullptr;

  delete chooseFamiglie;
  chooseFamiglie = nullptr;

  delete chooseEntrata;
  chooseEntrata = nullptr;

  delete choosePosti;
  choosePosti = nullptr;

  delete chooseFilm;
  chooseFilm = nullptr;
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

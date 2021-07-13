#include "mainwindow.h"
#include "controller.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      desktop(QApplication::desktop()),
      widget(new QWidget(this)),
      mainLayout(new QGridLayout()),
      v_layout(new QVBoxLayout()),
      buttonLayout(new QGridLayout()),
      title(new QLabel("Setup")),
      changeBtn(new QPushButton(QIcon(":/images/reverse.png"), "")),
      chooseUtenti(nullptr),
      chooseFamiglie(nullptr),
      chooseEntrata(nullptr),
      chooseSala(nullptr),
      choosePosti(nullptr),
      chooseFilm(nullptr),
      adminBtn(nullptr),
      clientBtn(nullptr),
      pathUser(new QLabel("name json utenti")),
      pathFamilies(new QLabel("name json famiglie")),
      pathEntrata(new QLabel("name json archivio entrate/abbonamenti")),
      pathPosti(new QLabel("name json postiOccupati")),
      pathSala(new QLabel("name json Sale")),
      pathFilm(new QLabel("name json film")),
      controller(nullptr),
      isVisReadBtn(true),
      prevAdmin("Admin"),
      prevChooseUtenti("Scegli file json per utenti"),
      prevChooseFamiglie("Scegli file json per famiglie") {
  changeBtn->setFixedWidth(50);

  title->setProperty("class", "title");

  v_layout->addWidget(title, Qt::AlignTop);

  mainLayout->addWidget(changeBtn, 0, 0, Qt::AlignRight);
  mainLayout->addLayout(v_layout, 1, 0, Qt::AlignCenter);
  mainLayout->addLayout(buttonLayout, 2, 0, Qt::AlignCenter);

  pathUser->setProperty("class", "path");
  pathUser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  pathFamilies->setProperty("class", "path");
  pathFamilies->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  pathPosti->setProperty("class", "path");
  pathPosti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  pathSala->setProperty("class", "path");
  pathSala->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  pathFilm->setProperty("class", "path");
  pathFilm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  pathEntrata->setProperty("class", "path");
  pathEntrata->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  buttonLayout->addWidget(pathUser, 0, 1, Qt::AlignCenter);
  buttonLayout->addWidget(pathFamilies, 1, 1, Qt::AlignCenter);
  buttonLayout->addWidget(pathEntrata, 2, 1, Qt::AlignCenter);
  buttonLayout->addWidget(pathSala, 3, 1, Qt::AlignCenter);
  buttonLayout->addWidget(pathPosti, 4, 1, Qt::AlignCenter);

  widget->setLayout(mainLayout);

  setCentralWidget(widget);

  resize(300, 300);
  move((desktop->width() - 300) / 2, (desktop->height() - 300) / 2);

  setStyle();
}

void MainWindow::setController(Controller *c) {
  controller = c;
  connect(changeBtn, SIGNAL(clicked()), this, SLOT(changeMenuSlot()));

  pathUser->setText(controller->getPathJsonUsers());
  pathFamilies->setText(controller->getPathJsonFamiglie());
  pathEntrata->setText(controller->getPathJsonEntrata());
  pathPosti->setText(controller->getPathJsonPosti());
  pathFilm->setText(controller->getPathJsonFilm());
  pathSala->setText(controller->getPathJsonSale());

  createLayoutSetup();
}

void MainWindow::setLabelPathUser(QString s) { pathUser->setText(s); }

void MainWindow::setLabelPathFamiglie(QString s) { pathFamilies->setText(s); }

void MainWindow::setLabelPathEntrata(QString s) { pathEntrata->setText(s); }

void MainWindow::setLabelPathPosti(QString s) { pathPosti->setText(s); }

void MainWindow::setLabelPathSale(QString s) { pathSala->setText(s); }

void MainWindow::setLabelPathFilm(QString s) { pathFilm->setText(s); }

void MainWindow::changeTitleAdmin(QString s) {
  prevAdmin = s;
  if (adminBtn) adminBtn->setText(s);
}

void MainWindow::changeTitleChooseSala(QString s) { pathFilm->setText(s); }

void MainWindow::changeTitleChooseUtenti(QString s) {
  prevChooseUtenti = s;
  if (chooseUtenti) {
    chooseUtenti->setText(s);
  }
}

void MainWindow::changeTitleChooseFamiglie(QString s) {
  prevChooseFamiglie = s;
  if (chooseFamiglie) {
    chooseFamiglie->setText(s);
  }
}

void MainWindow::changeTitleChooseEntrata(QString s) {
  prevChooseEntrata = s;
  if (chooseEntrata) {
    chooseEntrata->setText(s);
  }
}

void MainWindow::changeMenuSlot() { changeMenu(); }

void MainWindow::resizeMe() { adjustSize(); }

void MainWindow::changeMenu() {
  if (isVisReadBtn) {
    destroyLayoutSetup();
    createLayoutAdCl();

    isVisReadBtn = false;

  } else {
    destroyLayoutAdCl();
    createLayoutSetup();

    isVisReadBtn = true;
  }
  QTimer::singleShot(0, this, SLOT(resizeMe()));
}

void MainWindow::createLayoutAdCl() {
  title->setText("QTheater");

  if (!adminBtn) {
    adminBtn = new QPushButton(prevAdmin);
    adminBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    buttonLayout->addWidget(adminBtn, 0, 0, Qt::AlignCenter);

    connect(adminBtn, SIGNAL(clicked()), controller, SLOT(openAdmin()));
  }
  if (!clientBtn) {
    clientBtn = new QPushButton("Cliente");
    clientBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    buttonLayout->addWidget(clientBtn, 1, 0, Qt::AlignCenter);

    connect(clientBtn, SIGNAL(clicked()), controller, SLOT(openClient()));
  }

  isVisReadBtn = false;
}

void MainWindow::destroyLayoutAdCl() {
  prevAdmin = adminBtn->text();
  buttonLayout->removeWidget(adminBtn);
  buttonLayout->removeWidget(clientBtn);

  delete adminBtn;
  adminBtn = nullptr;

  delete clientBtn;
  clientBtn = nullptr;
}

void MainWindow::setPrevAdmin(const QString &value) { prevAdmin = value; }

void MainWindow::createLayoutSetup() {
  title->setText("Setup");
  if (!chooseUtenti) {
    chooseUtenti = new QPushButton(prevChooseUtenti);
    chooseUtenti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(chooseUtenti, SIGNAL(clicked()), controller, SLOT(loadUsersSlot()));
  }
  buttonLayout->addWidget(chooseUtenti, 0, 0, Qt::AlignCenter);

  if (!chooseFamiglie) {
    chooseFamiglie = new QPushButton(prevChooseFamiglie);
    chooseFamiglie->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(chooseFamiglie, SIGNAL(clicked()), controller,
            SLOT(loadFamiliesSlot()));
  }
  if (controller->getPathJsonUsers() != "")
    buttonLayout->addWidget(chooseFamiglie, 1, 0, Qt::AlignCenter);

  if (!chooseEntrata) {
    chooseEntrata = new QPushButton("Scegli file json per entrata film");
    chooseEntrata->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(chooseEntrata, SIGNAL(clicked()), controller,
            SLOT(loadEntrateSlot()));
  }
  if (controller->getPathJsonFamiglie() != "")
    buttonLayout->addWidget(chooseEntrata, 2, 0, Qt::AlignCenter);

  if (choosePosti == nullptr) {
    choosePosti = new QPushButton("Scegli file json per posti occupati");
    choosePosti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(choosePosti, SIGNAL(clicked()), controller, SLOT(loadPostiSlot()));
  }
  if (controller->getPathJsonUsers() != "")
    buttonLayout->addWidget(choosePosti, 3, 0, Qt::AlignCenter);

  if (!chooseSala) {
    chooseSala = new QPushButton("Scegli json per sala");
    chooseSala->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(chooseSala, SIGNAL(clicked()), controller, SLOT(loadSaleSlot()));
  }
  buttonLayout->addWidget(chooseSala, 4, 0, Qt::AlignCenter);

  if (!chooseFilm) {
    chooseFilm = new QPushButton("Scegli json per film");
    chooseFilm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(chooseFilm, SIGNAL(clicked()), controller, SLOT(loadFilmSlot()));
  }
  buttonLayout->addWidget(chooseFilm, 5, 0, Qt::AlignCenter);

  isVisReadBtn = true;
}

void MainWindow::destroyLayoutSetup() {
  if (chooseUtenti) prevChooseUtenti = chooseUtenti->text();
  if (chooseFamiglie) prevChooseFamiglie = chooseFamiglie->text();
  buttonLayout->removeWidget(chooseUtenti);
  buttonLayout->removeWidget(chooseFamiglie);
  buttonLayout->removeWidget(chooseEntrata);
  buttonLayout->removeWidget(choosePosti);
  buttonLayout->removeWidget(chooseFilm);
  buttonLayout->removeWidget(chooseSala);

  delete chooseUtenti;
  chooseUtenti = nullptr;

  delete chooseFamiglie;
  chooseFamiglie = nullptr;

  delete chooseEntrata;
  chooseEntrata = nullptr;

  delete choosePosti;
  choosePosti = nullptr;

  delete chooseSala;
  chooseSala = nullptr;

  delete chooseFilm;
  chooseFilm = nullptr;
}

void MainWindow::setStyle() {
  QFile file(":/qss/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
}

MainWindow *MainWindow::getMainwindow() { return this; }

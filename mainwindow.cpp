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
      chooseAbbonamenti(nullptr),
      adminBtn(nullptr),
      clientBtn(nullptr),
      pathUser(new QLabel("name json utenti")),
      pathFamilies(new QLabel("name json famiglie")),
      pathEntrata(new QLabel("name json archivio entrate/abbonamenti")),
      pathPosti(new QLabel("name json postiOccupati")),
      pathSala(new QLabel("name json Sale")),
      pathFilm(new QLabel("name json film")),
      pathAbbonamenti(new QLabel("name json ABbonamenti")),
      controller(nullptr),
      isVisReadBtn(true),
      prevAdmin("Admin"),
      prevChooseUtenti("Scegli file json per utenti"),
      prevChooseFamiglie("Scegli file json per famiglie"),
      prevChooseAbbonamenti("scegli file json per abbonamenti") {
  changeBtn->setMinimumWidth(50);
  changeBtn->setProperty("class", "changeBtn");

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

  pathAbbonamenti->setProperty("class", "path");
  pathAbbonamenti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  buttonLayout->addWidget(pathUser, 0, 1, Qt::AlignCenter);
  buttonLayout->addWidget(pathFamilies, 1, 1, Qt::AlignCenter);
  buttonLayout->addWidget(pathEntrata, 2, 1, Qt::AlignCenter);
  buttonLayout->addWidget(pathPosti, 3, 1, Qt::AlignCenter);
  buttonLayout->addWidget(pathSala, 4, 1, Qt::AlignCenter);
  buttonLayout->addWidget(pathFilm, 5, 1, Qt::AlignCenter);
  buttonLayout->addWidget(pathAbbonamenti, 6, 1, Qt::AlignCenter);

  widget->setLayout(mainLayout);

  setCentralWidget(widget);

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
  pathAbbonamenti->setText(controller->getPathJsonAbbonamenti());

  createLayoutAdCl();
  createLayoutSetup();

  showLayoutSetup();

  showPath();
}

void MainWindow::setLabelPathUser(const QString &s) { pathUser->setText(s); }

void MainWindow::setLabelPathFamiglie(const QString &s) {
  pathFamilies->setText(s);
}

void MainWindow::setLabelPathEntrata(const QString &s) {
  pathEntrata->setText(s);
}

void MainWindow::setLabelPathPosti(const QString &s) { pathPosti->setText(s); }

void MainWindow::setLabelPathSale(const QString &s) { pathSala->setText(s); }

void MainWindow::setLabelPathFilm(const QString &s) { pathFilm->setText(s); }

void MainWindow::setLabelPathAbbonamenti(const QString &s) {
  pathAbbonamenti->setText(s);
}

void MainWindow::changeTitleAdmin(const QString &s) {
  prevAdmin = s;
  if (adminBtn) adminBtn->setText(s);
}

void MainWindow::changeTitleChooseSala(const QString &s) {
  pathFilm->setText(s);
}

void MainWindow::changeTitleChooseAbbonamenti(const QString &s) {
  pathAbbonamenti->setText(s);
}

void MainWindow::changeTitleChooseUtenti(const QString &s) {
  prevChooseUtenti = s;
  if (chooseUtenti) {
    chooseUtenti->setText(s);
  }
}

void MainWindow::changeTitleChooseFamiglie(const QString &s) {
  prevChooseFamiglie = s;
  if (chooseFamiglie) {
    chooseFamiglie->setText(s);
  }
}

void MainWindow::changeTitleChooseEntrata(const QString &s) {
  prevChooseEntrata = s;
  if (chooseEntrata) {
    chooseEntrata->setText(s);
  }
}

void MainWindow::changeTitleChooseFilm(const QString &s) {
  prevChooseFilm = s;
  if (chooseFilm) {
    chooseFilm->setText(s);
  }
}

void MainWindow::changeMenuSlot() { changeMenu(); }

void MainWindow::resizeMe() { adjustSize(); }

void MainWindow::changeMenu() {
  if (isVisReadBtn) {
    hideLayoutSetup();

    showLayoutAdCLl();

    isVisReadBtn = false;

  } else {
    hideLayoutAdCLl();

    showLayoutSetup();

    isVisReadBtn = true;
  }
  showPath();
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
  buttonLayout->addWidget(chooseFamiglie, 1, 0, Qt::AlignCenter);

  if (!chooseEntrata) {
    chooseEntrata = new QPushButton("Scegli file json per entrata film");
    chooseEntrata->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(chooseEntrata, SIGNAL(clicked()), controller,
            SLOT(loadEntrateSlot()));
  }
  buttonLayout->addWidget(chooseEntrata, 2, 0, Qt::AlignCenter);

  if (!choosePosti) {
    choosePosti = new QPushButton("Scegli file json per posti occupati");
    choosePosti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(choosePosti, SIGNAL(clicked()), controller, SLOT(loadPostiSlot()));
  }
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

  if (!chooseAbbonamenti) {
    chooseAbbonamenti = new QPushButton("Scegli json per abbonamenti");
    chooseAbbonamenti->setSizePolicy(QSizePolicy::Expanding,
                                     QSizePolicy::Fixed);
  }
  buttonLayout->addWidget(chooseAbbonamenti, 6, 0, Qt::AlignCenter);
}

void MainWindow::hideLayoutAdCLl() {
  adminBtn->hide();
  clientBtn->hide();
}

void MainWindow::showLayoutAdCLl() {
  hideLayoutSetup();

  adminBtn->show();
  clientBtn->show();

  isVisReadBtn = false;
  title->setText("QTheater");
}

void MainWindow::setPrevAdmin(const QString &value) { prevAdmin = value; }

void MainWindow::hideLayoutSetup() {
  chooseUtenti->hide();
  chooseFamiglie->hide();
  chooseEntrata->hide();
  choosePosti->hide();
  chooseFilm->hide();
  chooseSala->hide();
  chooseAbbonamenti->hide();

  isVisReadBtn = false;
}

void MainWindow::showLayoutSetup() {
  hideLayoutAdCLl();

  chooseUtenti->show();

  if (controller->getPathJsonUsers() != "") {
    chooseFamiglie->show();
    chooseEntrata->show();
    choosePosti->show();
    chooseAbbonamenti->show();
  } else {
    chooseFamiglie->hide();
    chooseEntrata->hide();
    choosePosti->hide();
    chooseAbbonamenti->hide();
  }
  chooseFilm->show();
  chooseSala->show();

  isVisReadBtn = true;
  title->setText("Setup");
}

void MainWindow::showPath() {
  if (controller->getPathJsonUsers() == "") {
    pathUser->hide();
  }
  if (controller->getPathJsonFamiglie() == "") {
    pathFamilies->hide();
  }
  if (controller->getPathJsonEntrata() == "") {
    pathEntrata->hide();
  }
  if (controller->getPathJsonFilm() == "") {
    pathFilm->hide();
  }
  if (controller->getPathJsonPosti() == "") {
    pathPosti->hide();
  }
  if (controller->getPathJsonSale() == "") {
    pathSala->hide();
  }
  if (controller->getPathJsonAbbonamenti() == "") {
    pathAbbonamenti->hide();
  }
}

void MainWindow::closeEvent(QCloseEvent *event) {
  event->ignore();
  if (QMessageBox::Yes ==
      QMessageBox::question(this, "Attenzione!", "Confermi di voler uscire?",
                            QMessageBox::Yes | QMessageBox::No)) {
    event->accept();
  }
}

void MainWindow::setStyle() {
  QFile file(":/qss/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
}

MainWindow *MainWindow::getMainwindow() { return this; }

#include "admin.h"
#include "controller.h"

Admin::Admin(Controller *c, MainWindow *parent)
    : desktop(QApplication::desktop()),
      baseLayout(new QGridLayout()),
      mainLayout(new QVBoxLayout()),

      p(parent),

      admin(new QLabel("Admin")),

      listAbb(new QListWidget()),
      listUt(new QListWidget()),
      listFam(new QListWidget()),
      listFilm(new QListWidget()),
      listSala(new QListWidget()),

      labelAbb(new QLabel("Abbonamenti")),
      labelUt(new QLabel("Utenti")),
      labelFam(new QLabel("Famiglie")),
      labelFilm(new QLabel("Film")),
      labelSala(new QLabel("Sala")),

      widget(new QWidget()),

      addFilm(new QPushButton("add Film")),
      addSala(new QPushButton("add Sala")),

      widgetFilm(nullptr),
      filmLayout(nullptr),
      nomeFilm(nullptr),
      salaFilm(nullptr),
      saveFilm(nullptr),

      widgetSala(nullptr),
      salaLayout(nullptr),
      nomeSala(nullptr),
      righeSala(nullptr),
      colonneSala(nullptr),
      saveSala(nullptr),

      controller(c) {
  setWindowTitle(QString("Admin"));

  QFont font;
  font.setPointSize(50);
  font.setBold(true);

  admin->setFont(font);
  admin->setProperty("class", "title");

  mainLayout->addWidget(admin, 0, Qt::AlignCenter);
  mainLayout->addLayout(baseLayout);

  widget->setLayout(mainLayout);

  font.setPointSize(15);

  labelAbb->setFont(font);
  labelAbb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  listAbb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  labelFam->setFont(font);
  labelFam->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  listFam->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  labelUt->setFont(font);
  labelUt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  listUt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  connect(listAbb, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(getClickAbb()));
  connect(listFam, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(getClickFam()));
  connect(listUt, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(getClickUt()));
  connect(addFilm, SIGNAL(clicked()), this, SLOT(addFilmLayout()));
  connect(addSala, SIGNAL(clicked()), this, SLOT(addSalaLayout()));

  baseLayout->addWidget(labelAbb, 0, 0, Qt::AlignCenter);
  baseLayout->addWidget(listAbb, 1, 0);

  baseLayout->addWidget(labelUt, 0, 1, Qt::AlignCenter);
  baseLayout->addWidget(listUt, 1, 1);

  baseLayout->addWidget(labelFam, 0, 2, Qt::AlignCenter);
  baseLayout->addWidget(listFam, 1, 2);

  baseLayout->addWidget(labelFilm, 2, 0, Qt::AlignCenter);
  baseLayout->addWidget(listFilm, 3, 0);
  baseLayout->addWidget(addFilm, 4, 0);

  baseLayout->addWidget(labelSala, 2, 1, Qt::AlignCenter);
  baseLayout->addWidget(listSala, 3, 1);
  baseLayout->addWidget(addSala, 4, 1);

  resize(1000, 400);

  setCentralWidget(widget);
}

void Admin::addUtente(const QString &s) {
  QListWidgetItem *item = new QListWidgetItem(s);
  listUt->addItem(item);
}

void Admin::addFamiglia(const QString &s) {
  QListWidgetItem *item = new QListWidgetItem(s);
  listFam->addItem(item);
}

void Admin::addEntrata(const QString &s, const QString &cod) {
  QLabelCF *lbl = new QLabelCF(new QLabel(s), cod);
  QListWidgetItem *item = new QListWidgetItem();
  listAbb->addItem(item);
  item->setSelected(false);
  listAbb->setItemWidget(item, lbl);
}

void Admin::addFilmLayout() {
  widgetFilm = new QWidget();
  filmLayout = new QGridLayout;
  nomeFilm = new QLineEditClickable;
  salaFilm = new QLineEditClickable;
  saveFilm = new QPushButton("Salva");

  filmLayout->addWidget(nomeFilm, 0, 0);
  filmLayout->addWidget(salaFilm, 1, 0);
  filmLayout->addWidget(saveFilm, 2, 0);

  widgetFilm->setLayout(filmLayout);
  widgetFilm->show();

  connect(saveFilm, SIGNAL(clicked()), controller, SLOT(newFilm()));
}

void Admin::addSalaLayout() {
  widgetSala = new QWidget();
  salaLayout = new QGridLayout;
  nomeSala = new QLineEditClickable;
  righeSala = new QLineEditClickable;
  colonneSala = new QLineEditClickable;
  saveSala = new QPushButton("Salva");

  salaLayout->addWidget(nomeSala, 0, 0);
  salaLayout->addWidget(righeSala, 1, 0);
  salaLayout->addWidget(colonneSala, 2, 0);
  salaLayout->addWidget(saveSala, 3, 0);

  nomeSala->setText("nome Sala");
  righeSala->setText("numero righe");
  colonneSala->setText("numero colonne");

  widgetSala->setLayout(salaLayout);
  widgetSala->show();

  connect(saveSala, SIGNAL(clicked()), controller, SLOT(newSala()));
}

void Admin::clearListUtenti() { listUt->clear(); }

void Admin::clearListFamiglie() { listFam->clear(); }

void Admin::clearListEntrate() { listAbb->clear(); }

QString Admin::getNomeFilm() { return nomeFilm->text(); }

QString Admin::getSalaFilm() { return salaFilm->text(); }

QString Admin::getColonneSala() { return colonneSala->text(); }

QString Admin::getRigheSala() { return righeSala->text(); }

void Admin::getClickFam() {
  qDebug() << "Famiglia " << listFam->currentItem()->text();
}

void Admin::getClickFilm() {
  qDebug() << "film " << listFilm->currentItem()->text();
}

void Admin::getClickUt() {
  qDebug() << "Utente " << listUt->currentItem()->text();
}

void Admin::getClickAbb() {
  QLabelCF *lbl =
      dynamic_cast<QLabelCF *>(listAbb->itemWidget(listAbb->currentItem()));
  qDebug() << lbl->text() << " -- " << lbl->getCf();
}

QString Admin::getNomeSala() { return nomeSala->text(); }

void Admin::closeEvent(QCloseEvent *event) {
  p->changeTitleAdmin("Admin");
  event->accept();
}

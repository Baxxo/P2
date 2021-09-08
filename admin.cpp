#include "admin.h"
#include "controller.h"

#include <QTimer>

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

      utility(new QLabel("Premi due volte per eliminare un abbonamento")),

      widget(new QWidget()),

      titoloFilm(new QLabel),
      addFilm(new QPushButton("aggiungi Film")),
      nomeSalaLabel(new QLabel),
      addSala(new QPushButton("aggiungi Sala")),
      utilityFilm(nullptr),

      widgetFilm(nullptr),
      filmLayout(nullptr),
      nomeFilm(nullptr),
      saveFilm(nullptr),

      widgetSala(nullptr),
      salaLayout(nullptr),
      nomeSala(nullptr),
      righeSala(nullptr),
      colonneSala(nullptr),
      saveSala(nullptr),

      regola(new QComboBox()),

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

  regola->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  regola->setFont(font);
  regola->addItem("bianca");
  regola->addItem("gialla");
  regola->addItem("arancione");
  regola->addItem("rossa");

  labelAbb->setFont(font);
  labelAbb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  listAbb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  labelFam->setFont(font);
  labelFam->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  listFam->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  labelUt->setFont(font);
  labelUt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  listUt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  baseLayout->addWidget(labelAbb, 0, 0, Qt::AlignCenter);
  baseLayout->addWidget(listAbb, 1, 0);

  baseLayout->addWidget(utility, 2, 0);

  baseLayout->addWidget(labelUt, 0, 1, Qt::AlignCenter);
  baseLayout->addWidget(listUt, 1, 1);

  baseLayout->addWidget(labelFam, 0, 2, Qt::AlignCenter);
  baseLayout->addWidget(listFam, 1, 2);

  baseLayout->addWidget(labelFilm, 3, 0, Qt::AlignCenter);
  baseLayout->addWidget(listFilm, 4, 0);
  baseLayout->addWidget(addFilm, 5, 0);

  baseLayout->addWidget(labelSala, 3, 1, Qt::AlignCenter);
  baseLayout->addWidget(listSala, 4, 1);
  baseLayout->addWidget(addSala, 5, 1);

  baseLayout->addWidget(regola, 2, 2, Qt::AlignCenter);

  connect(listAbb, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this,
          SLOT(getClickAbb()));
  connect(addFilm, SIGNAL(clicked()), this, SLOT(addFilmLayout()));
  connect(addSala, SIGNAL(clicked()), this, SLOT(addSalaLayout()));
  connect(regola, SIGNAL(currentTextChanged(const QString &)), controller,
          SLOT(setRegola(const QString &)));

  resize(1000, 400);

  setCentralWidget(widget);
}

void Admin::addUtenteinList(const QString &s) {
  QListWidgetItem *item = new QListWidgetItem(s);
  listUt->addItem(item);
}

void Admin::addFamigliainList(const QString &s) {
  QListWidgetItem *item = new QListWidgetItem(s);
  listFam->addItem(item);
}

void Admin::addFilminList(const QString &s) {
  QListWidgetItem *item = new QListWidgetItem(s);
  listFilm->addItem(item);
}

void Admin::addSaleinList(const QString &s) {
  QListWidgetItem *item = new QListWidgetItem(s);
  listSala->addItem(item);
}

void Admin::clearListUtenti() { listUt->clear(); }

void Admin::clearListFamiglie() { listFam->clear(); }

void Admin::clearListAbbonamenti() { listAbb->clear(); }

void Admin::clearListFilm() { listFilm->clear(); }

void Admin::clearListSale() { listSala->clear(); }

void Admin::clearListEntrate() { listAbb->clear(); }

QString Admin::getNomeFilm() { return nomeFilm->text(); }

QString Admin::getSalaFilm() { return listSala->currentItem()->text(); }

void Admin::setUtilityFilm(const QString &s) {
  utilityFilm->setText(s);
  QTimer::singleShot(3000, this, SLOT(clearUtilityFilm()));
}

QString Admin::getColonneSala() { return colonneSala->text(); }

QString Admin::getRigheSala() { return righeSala->text(); }

void Admin::addEntrata(const QString &s, const QString &cod) {
  QLabelCF *lbl = new QLabelCF(new QLabel(s), cod);
  QListWidgetItem *item = new QListWidgetItem();
  listAbb->addItem(item);
  item->setSelected(false);
  listAbb->setItemWidget(item, lbl);
}

void Admin::addAbbonamento(const QString &s, const QString &cod) {
  QLabelCF *lbl = new QLabelCF(new QLabel(s), cod);
  QListWidgetItem *item = new QListWidgetItem();
  listAbb->addItem(item);
  item->setSelected(false);
  listAbb->setItemWidget(item, lbl);
}

void Admin::addFilmLayout() {
  widgetFilm = new QWidget();
  filmLayout = new QGridLayout;
  titoloFilm->setText("Inserisci titolo del film");
  nomeSalaLabel->setText("Inserisci nome della sala");
  utilityFilm = new QLabel();
  nomeFilm = new QLineEditClickable;
  saveFilm = new QPushButton("Salva");

  filmLayout->addWidget(titoloFilm, 0, 0);
  filmLayout->addWidget(nomeFilm, 1, 0);
  filmLayout->addWidget(nomeSalaLabel, 2, 0);
  filmLayout->addWidget(listSala, 3, 0);
  filmLayout->addWidget(saveFilm, 4, 0);
  filmLayout->addWidget(utilityFilm, 5, 0);

  widgetFilm->setLayout(filmLayout);
  widgetFilm->show();

  connect(saveFilm, SIGNAL(clicked()), controller, SLOT(newFilm()));
}

QString Admin::getNomeSala() { return nomeSala->text(); }

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

void Admin::clearUtility() {
  utility->setText("Premi due volte per eliminare un abbonamento");
}

void Admin::clearUtilityFilm() {
  if (utilityFilm) utilityFilm->setText("");
}

void Admin::getClickAbb() {
  QLabelCF *lbl =
      dynamic_cast<QLabelCF *>(listAbb->itemWidget(listAbb->currentItem()));
  QString prev = lbl->text();
  if (controller->removeAbbonamento(lbl->getCf())) {
    controller->loadEntrateInAdmin();
    utility->setText(utility->text() + "\n" + prev + " rimosso con Successo");
  } else {
    utility->setText(utility->text() +
                     "\nErrore nella rimozione dell' abbonamento " + prev);
  }
  QTimer::singleShot(3000, this, SLOT(clearUtility()));
}

void Admin::closeEvent(QCloseEvent *event) {
  p->changeTitleAdmin("Admin");
  event->accept();
}

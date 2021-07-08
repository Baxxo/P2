#include "biglietto_view.h"
#include "controller.h"

Biglietto_View::Biglietto_View(Controller *c, QWidget *parent)
    : QWidget(parent),
      controller(c),
      prezzo(0),
      film(""),
      labelTipo(new QLabel("Scegli tipo Entrata e poi premi ok")),
      tipologia(new QComboBox),
      layoutTipologia(new QVBoxLayout),
      mainWidget(new QWidget(this)),
      widgetSing(new QWidget),
      salaWidget(new QWidget),
      compraLayout(new QVBoxLayout),
      mainLayout(new QGridLayout),
      compraBiglietto(new QPushButton("Compra")),
      labelListaFilm(new QLabel("Lista film disponibli")),
      listaFilm(new QListWidget),
      tipologiaBtn(new QPushButton("OK")),
      utenteBigl(new QVBoxLayout),
      searchUtility(new QLabel(QString("Inserisci CF da cercare"))),
      search(new QLineEditClickable("inserisci codice fiscale da cercare")),
      searchBtn(new QPushButton("ok")),
      salaLayout(new QVBoxLayout),
      selectSeat(new QPushButton("scegli un posto")),
      posti(new QTableWidget(2, 3))

{
  tipologia->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  compraBiglietto->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  tipologiaBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  widgetSing->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  listaFilm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  search->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  searchBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  salaWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  selectSeat->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  posti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  //------------------------
  utenteBigl->addWidget(searchUtility, Qt::AlignCenter);
  utenteBigl->addWidget(search, Qt::AlignCenter);
  utenteBigl->addWidget(searchBtn, Qt::AlignCenter);

  widgetSing->setLayout(utenteBigl);
  //------------------------

  layoutTipologia->addWidget(labelTipo, Qt::AlignCenter);
  layoutTipologia->addWidget(tipologia, Qt::AlignCenter);
  layoutTipologia->addWidget(tipologiaBtn, Qt::AlignCenter);

  mainLayout->addLayout(layoutTipologia, 0, 0, Qt::AlignCenter);

  compraLayout->addWidget(labelListaFilm, Qt::AlignTop);
  compraLayout->addWidget(listaFilm, Qt::AlignTop);
  compraLayout->addWidget(selectSeat, Qt::AlignRight);
  compraLayout->addWidget(compraBiglietto, Qt::AlignBottom);

  mainLayout->addLayout(compraLayout, 1, 0, Qt::AlignCenter);

  mainWidget->setLayout(mainLayout);
  mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  salaLayout->addWidget(posti);
  salaWidget->setLayout(salaLayout);
  salaWidget->hide();

  tipologia->insertItem(0, "Singolo");
  tipologia->insertItem(1, "Abbonamento");

  setWindowTitle(QString("Acquisto biglietto"));

  connect(tipologiaBtn, SIGNAL(clicked()), this, SLOT(showSearch()));
  connect(searchBtn, SIGNAL(clicked()), controller, SLOT(stpBigl()));
  connect(selectSeat, SIGNAL(clicked()), controller, SLOT(showSala()));

  setStyle();
}

void Biglietto_View::setStyle() {
  QFile file(":/qss/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
}

QString Biglietto_View::getSearch() { return search->text(); }

QString Biglietto_View::getTipologia() { return tipologia->currentText(); }

void Biglietto_View::getSalaView() { salaWidget->show(); }

void Biglietto_View::setUtilitySearchText(const QString &s) {
  searchUtility->setText(s);
}

void Biglietto_View::showSearch() { widgetSing->show(); }

void Biglietto_View::resizeMe() { adjustSize(); }

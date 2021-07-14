#include "biglietto_view.h"
#include "controller.h"

Biglietto_View::Biglietto_View(Controller *c, QWidget *parent)
    : QWidget(parent),
      controller(c),
      prezzo(0),
      film(""),

      mainLayout(new QGridLayout),

      labelTipo(new QLabel("Scegli tipo Entrata e poi premi ok")),
      tipologia(new QComboBox),
      tipologiaBtn(new QPushButton("OK")),
      layoutTipologia(new QVBoxLayout),

      searchUtility(new QLabel(QString("Inserisci CF da cercare"))),
      search(new QLineEditClickable("inserisci codice fiscale da cercare")),
      searchBtn(new QPushButton("ok")),
      utenteBigl(new QVBoxLayout),
      widgetSearchCf(new QWidget),

      labelListaFilm(new QLabel("Lista film disponibli")),
      listaFilm(new QListWidget),
      compraLayout(new QVBoxLayout),

      selectSeat(new QPushButton("scegli un posto")),
      salaLayout(new QVBoxLayout),
      salaWidget(new QWidget),

      posti(new QTableWidget(2, 3)),

      compraBiglietto(new QPushButton("Compra"))

{
  //  parte per selezionare se biglietto o abbonamento
  labelTipo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  layoutTipologia->addWidget(labelTipo, Qt::AlignCenter);

  tipologia->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  layoutTipologia->addWidget(tipologia, Qt::AlignCenter);

  // manca aggiungere combobox con utenti o lista abbonamenti

  tipologiaBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  layoutTipologia->addWidget(tipologiaBtn, Qt::AlignCenter);

  mainLayout->addLayout(layoutTipologia, 0, 0, Qt::AlignCenter);

  connect(tipologiaBtn, SIGNAL(clicked()), this, SLOT(showSearch()));

  //-------------------------------------------------------------------------

  // widget per ricerca cf utenti
  searchUtility->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  utenteBigl->addWidget(searchUtility, Qt::AlignCenter);

  search->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  utenteBigl->addWidget(search, Qt::AlignCenter);

  searchBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  utenteBigl->addWidget(searchBtn, Qt::AlignCenter);

  widgetSearchCf->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  widgetSearchCf->setLayout(utenteBigl);

  connect(searchBtn, SIGNAL(clicked()), controller, SLOT(stpBigl()));

  //-------------------------------------------------------------------------

  // lista film

  labelListaFilm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  compraLayout->addWidget(labelListaFilm, Qt::AlignTop);

  listaFilm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  compraLayout->addWidget(listaFilm, Qt::AlignTop);

  //-------------------------------------------------------------------------

  // selezione del posto desiderato

  selectSeat->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  compraLayout->addWidget(selectSeat, Qt::AlignRight);

  connect(selectSeat, SIGNAL(clicked()), controller, SLOT(showSala()));

  // widget per selezionare posto in sala
  salaLayout->addWidget(posti);
  salaWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  salaWidget->setLayout(salaLayout);
  salaWidget->hide();

  // tabella per posti
  posti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  //-------------------------------------------------------------------------

  compraBiglietto->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  compraLayout->addWidget(compraBiglietto, Qt::AlignBottom);

  mainLayout->addLayout(compraLayout, 1, 0, Qt::AlignCenter);

  tipologia->insertItem(0, "Biglietto");
  tipologia->insertItem(1, "Abbonamento");

  setWindowTitle(QString("Acquisto biglietto"));

  setLayout(mainLayout);

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

void Biglietto_View::showSalaView() {
  salaWidget->show();
  resizeSala();
}

void Biglietto_View::setUtilitySearchText(const QString &s) {
  searchUtility->setText(s);
}

void Biglietto_View::showSearch() { widgetSearchCf->show(); }

void Biglietto_View::resizeMe() { adjustSize(); }

void Biglietto_View::resizeSala() {
  qDebug() << "ciao";
  if (salaWidget) salaWidget->adjustSize();
}

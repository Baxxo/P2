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

      posti(nullptr),
      nomeSala(nullptr),
      colonneMax(nullptr),

      compraBiglietto(new QPushButton("Compra")),

      postiOccupati(nullptr),

      mainWidget(new QWidget(this)),
      widgetSing(new QWidget)

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

  //-------------------------------------------------------------------------

  compraBiglietto->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  compraLayout->addWidget(compraBiglietto, Qt::AlignBottom);

  widgetSearchCf->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  widgetSearchCf->setLayout(utenteBigl);

  mainLayout->addLayout(compraLayout, 1, 0, Qt::AlignCenter);

  tipologia->insertItem(0, "Biglietto");
  tipologia->insertItem(1, "Abbonamento");

  setWindowTitle(QString("Acquisto biglietto"));

  setLayout(mainLayout);

  connect(listaFilm, SIGNAL(itemClicked(QListWidgetItem *)), controller,
          SLOT(showSala()));
  connect(listaFilm, SIGNAL(itemClicked(QListWidgetItem *)), controller,
          SLOT(setPostiOccupati()));

  setStyle();
}

void Biglietto_View::setStyle() {
  QFile file(":/qss/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
}

void Biglietto_View::getSalaView() {
  connect(posti, SIGNAL(cellClicked(int, int)), controller,
          SLOT(newPostoOccupato()));
  salaWidget->show();
}

void Biglietto_View::addFilminList(const QString &s) {
  QListWidgetItem *item = new QListWidgetItem(s);
  listaFilm->addItem(item);
}

int Biglietto_View::getCurrentColumn() { return posti->currentColumn(); }

int Biglietto_View::getCurrentRow() { return posti->currentRow(); }

QString Biglietto_View::getNomeSala() { return nomeSala->text(); }

QString Biglietto_View::getSelectedFilm() {
  QListWidgetItem *current = listaFilm->currentItem();
  if (current) {
    return listaFilm->currentItem()->text();
  } else {
    controller->openError("seleziona un film prima");
    return nullptr;
  }
}

int Biglietto_View::getColonneMax() { return colonneMax->text().toInt(); }

void Biglietto_View::setPostoOccupato(int r, int c) {
  QTableWidgetItem *item = new QTableWidgetItem("occupato");
  item->setBackgroundColor("red");
  posti->setItem(r, c, item);
}

void Biglietto_View::createSalaView(int r, int c, const QString &f) {
  if (posti) {
    delete posti;
  }
  if (nomeSala) {
    delete nomeSala;
  }

  salaWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  posti = new QTableWidget(r, c);
  // posti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  nomeSala = new QLabel;
  colonneMax = new QLabel;
  nomeSala->setText(f);
  colonneMax->setText(QString::number(c));
  posti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  nomeSala->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  colonneMax->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  salaLayout->addWidget(nomeSala);
  salaLayout->addWidget(posti);
  salaLayout->addWidget(colonneMax);
  salaWidget->setLayout(salaLayout);

  salaWidget->hide();

  getSalaView();
}

void Biglietto_View::clearListFilm() { listaFilm->clear(); }

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

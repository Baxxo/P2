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

      selectedItemSearch(new QLabel("Selezionato: ")),
      searchUtility(new QLabel("")),
      listaSearch(new QListWidget),
      utenteBigl(new QVBoxLayout),
      widgetSearchCf(new QWidget),

      labelListaFilm(new QLabel("Cliccare una volta sul film desiderato")),
      listaFilm(new QListWidget),
      compraLayout(new QVBoxLayout),

      salaLayout(new QVBoxLayout),
      salaWidget(new QWidget),

      posti(nullptr),
      compraBiglietto(new QPushButton("Compra")),

      postiOccupati(nullptr),

      mainWidget(new QWidget(this)),
      widgetSing(new QWidget),
      selectName(""),
      titleSearch(""),
      isAlreadySelectdSearch(false),
      selectFromSearch("")

{
  selectedItemSearch->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  layoutTipologia->addWidget(selectedItemSearch, Qt::AlignCenter);
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
  searchUtility->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  utenteBigl->addWidget(searchUtility, Qt::AlignCenter);

  utenteBigl->addWidget(listaSearch, Qt::AlignCenter);
  widgetSearchCf->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  widgetSearchCf->setLayout(utenteBigl);

  //-------------------------------------------------------------------------

  // lista film

  labelListaFilm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  compraLayout->addWidget(labelListaFilm, Qt::AlignTop);

  listaFilm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  compraLayout->addWidget(listaFilm, Qt::AlignTop);

  compraBiglietto->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  compraLayout->addWidget(compraBiglietto, Qt::AlignBottom);

  widgetSearchCf->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  widgetSearchCf->setLayout(utenteBigl);

  mainLayout->addLayout(compraLayout, 1, 0, Qt::AlignCenter);

  tipologia->insertItem(0, "Biglietto");
  tipologia->insertItem(1, "Abbonamento");

  setWindowTitle(QString("Acquisto biglietto"));

  setLayout(mainLayout);

  connect(listaSearch, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this,
          SLOT(getNameSelect(QListWidgetItem *)));

  connect(listaFilm, SIGNAL(itemClicked(QListWidgetItem *)), controller,
          SLOT(showSala()));

  connect(listaFilm, SIGNAL(itemClicked(QListWidgetItem *)), controller,
          SLOT(setPostiOccupati()));

  connect(compraBiglietto, SIGNAL(clicked()), controller, SLOT(buyBiglietto()));

  connect(listaSearch, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this,
          SLOT(selectFromListSearch(QListWidgetItem *)));

  setStyle();
}

void Biglietto_View::setStyle() {
  QFile file(":/qss/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
  widgetSearchCf->setStyleSheet(styleSheet);
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

void Biglietto_View::addEntrataToLista(const QString &text,
                                       const QString &cod) {
  QListWidgetItem *itemN = new QListWidgetItem();
  QLabelCF *widgetText = new QLabelCF(new QLabel(text), cod);

  listaSearch->addItem(itemN);
  itemN->setSelected(false);
  listaSearch->setItemWidget(itemN, widgetText);
}

int Biglietto_View::getCurrentColumn() { return posti->currentColumn(); }

int Biglietto_View::getCurrentRow() { return posti->currentRow(); }

QString Biglietto_View::getSelectedFilm() {
  QListWidgetItem *current = listaFilm->currentItem();
  if (current) {
    return listaFilm->currentItem()->text();
  } else {
    controller->openError("seleziona un film prima");
    return nullptr;
  }
}

void Biglietto_View::setPostoOccupato(unsigned int r, unsigned int c,
                                      QString regola) {
  QTableWidgetItem *item = new QTableWidgetItem("occupato");
  item->setBackgroundColor("red");
  item->setFlags(item->flags() & ~Qt::ItemIsEditable);
  posti->setItem(static_cast<int>(r), static_cast<int>(c), item);
  int x =
      (static_cast<int>(r) * controller->getColonneMax()) + static_cast<int>(c);
  if (regola == "gialla") {
    QTableWidgetItem *itemdist1 = new QTableWidgetItem("distanziamento");
    QTableWidgetItem *itemdist2 = new QTableWidgetItem("distanziamento");
    itemdist1->setBackgroundColor("yellow");
    itemdist2->setBackgroundColor("yellow");
    if (x % controller->getColonneMax() == controller->getColonneMax() - 1) {
      posti->setItem(static_cast<int>(r), static_cast<int>(c - 1), itemdist1);
    }
    if (x % controller->getColonneMax() == 0) {
      posti->setItem(static_cast<int>(r), static_cast<int>(c + 1), itemdist1);
    } else {
      posti->setItem(static_cast<int>(r), static_cast<int>(c - 1), itemdist1);
      posti->setItem(static_cast<int>(r), static_cast<int>(c + 1), itemdist2);
    }
  }
  if (regola == "arancione") {
    QTableWidgetItem *itemdist1 = new QTableWidgetItem("distanziamento");
    QTableWidgetItem *itemdist2 = new QTableWidgetItem("distanziamento");
    QTableWidgetItem *itemdist3 = new QTableWidgetItem("distanziamento");
    QTableWidgetItem *itemdist4 = new QTableWidgetItem("distanziamento");
    itemdist1->setBackgroundColor("yellow");
    itemdist2->setBackgroundColor("yellow");
    itemdist3->setBackgroundColor("yellow");
    itemdist4->setBackgroundColor("yellow");
    if (x % static_cast<int>(controller->getColonneMax()) ==
        static_cast<int>(controller->getColonneMax()) - 1) {
      posti->setItem(static_cast<int>(r), static_cast<int>(c - 1), itemdist1);
      posti->setItem(static_cast<int>(r), static_cast<int>(c - 2), itemdist2);
    }
    if (x % static_cast<int>(controller->getColonneMax()) == 0) {
      posti->setItem(static_cast<int>(r), static_cast<int>(c + 1), itemdist1);
      posti->setItem(static_cast<int>(r), static_cast<int>(c + 2), itemdist2);
    }
    if (x % static_cast<int>(controller->getColonneMax()) ==
        static_cast<int>(controller->getColonneMax()) - 2) {
      posti->setItem(static_cast<int>(r), static_cast<int>(c - 1), itemdist1);
      posti->setItem(static_cast<int>(r), static_cast<int>(c - 2), itemdist2);
      posti->setItem(static_cast<int>(r), static_cast<int>(c + 1), itemdist3);
    }
    if (x % static_cast<int>(controller->getColonneMax()) == 1) {
      posti->setItem(static_cast<int>(r), static_cast<int>(c + 1), itemdist1);
      posti->setItem(static_cast<int>(r), static_cast<int>(c + 2), itemdist2);
      posti->setItem(static_cast<int>(r), static_cast<int>(c - 1), itemdist3);
    } else {
      posti->setItem(static_cast<int>(r), static_cast<int>(c - 1), itemdist1);
      posti->setItem(static_cast<int>(r), static_cast<int>(c - 2), itemdist2);
      posti->setItem(static_cast<int>(r), static_cast<int>(c + 1), itemdist3);
      posti->setItem(static_cast<int>(r), static_cast<int>(c + 2), itemdist4);
    }
  }
  connect(posti, SIGNAL(cellClicked(int, int)), this, SLOT(hideSalaView()));
  labelListaFilm->setText("Posto scelto correttamente");
}

void Biglietto_View::createSalaView(unsigned int r, unsigned int c) {
  if (posti) {
    delete posti;
  }

  salaWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  posti = new QTableWidget(static_cast<int>(r), static_cast<int>(c));
  posti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  salaLayout->addWidget(posti);
  salaWidget->setLayout(salaLayout);

  salaWidget->hide();

  getSalaView();
}

void Biglietto_View::clearListFilm() { listaFilm->clear(); }

QString Biglietto_View::getTipologia() { return tipologia->currentText(); }

void Biglietto_View::showSalaView() {
  salaWidget->show();
  resizeSala();
}

void Biglietto_View::getNameSelect(QListWidgetItem *item) {
  QLabelCF *lbl = dynamic_cast<QLabelCF *>(listaSearch->itemWidget(item));

  selectName = lbl->getCf();
}

void Biglietto_View::popolaLista(int index) {
  listaSearch->clear();
  controller->popolaEntrateBiglietto(index);
}

void Biglietto_View::selectFromListSearch(QListWidgetItem *item) {
  QLabelCF *lbl = dynamic_cast<QLabelCF *>(listaSearch->itemWidget(item));

  lbl->setStyleSheet("QLabel { background-color : LightGreen;}");
  lbl->setSelect(true);
  isAlreadySelectdSearch = true;
  selectFromSearch = lbl->text();

  selectedItemSearch->setText("Selezionato: " + selectFromSearch);
  listaSearch->setItemWidget(item, lbl);

  widgetSearchCf->close();
}

void Biglietto_View::setUtilitySearchText(const QString &s) {
  searchUtility->setText(s);
}

QString Biglietto_View::getSelectName() const { return selectName; }

void Biglietto_View::setTitleSearch(const QString &t) {
  titleSearch = "Clicca due volte per selezionare " + t;
}

QString Biglietto_View::getSelectFromSearch() const { return selectFromSearch; }

void Biglietto_View::showSearch() {
  listaSearch->clear();
  controller->popolaEntrateBiglietto(tipologia->currentIndex());
  searchUtility->setText(titleSearch);
  widgetSearchCf->show();
}

void Biglietto_View::resizeMe() { adjustSize(); }

void Biglietto_View::hideSalaView() { salaWidget->hide(); }

void Biglietto_View::resizeSala() {
  if (salaWidget) salaWidget->adjustSize();
}

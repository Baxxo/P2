#include "biglietto_view.h"
#include "controller.h"

Biglietto_View::Biglietto_View(Controller *c, QWidget *parent)
    : QWidget(parent), controller(c), prezzo(0), film(""),
      tipologia(new QComboBox), layoutTipologia(new QVBoxLayout),
      mainWidget(new QWidget(this)), widgetSing(new QWidget),
      salaWidget(new QWidget), compraLayout(new QVBoxLayout),
      mainLayout(new QGridLayout), compraBiglietto(new QPushButton("Compra")),
      listaFilm(new QListWidget), tipologiaBtn(new QPushButton("OK")),
      utenteBigl(new QVBoxLayout), search(new QLineEditClickable),
      searchBtn(new QPushButton("ok")), salaLayout(new QVBoxLayout),
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

  salaWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  selectSeat->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  posti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  compraLayout->addWidget(listaFilm, Qt::AlignTop);
  compraLayout->addWidget(compraBiglietto, Qt::AlignBottom);
  compraLayout->addWidget(selectSeat, Qt::AlignRight);

  layoutTipologia->addWidget(tipologia, Qt::AlignCenter);
  layoutTipologia->addWidget(tipologiaBtn, Qt::AlignCenter);

  salaLayout->addWidget(posti);

  mainLayout->addLayout(layoutTipologia, 0, 0, Qt::AlignCenter);
  mainLayout->addLayout(compraLayout, 1, 1, Qt::AlignCenter);

  utenteBigl->addWidget(search, Qt::AlignCenter);
  utenteBigl->addWidget(searchBtn, Qt::AlignCenter);

  mainWidget->setLayout(mainLayout);

  mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  widgetSing->setLayout(utenteBigl);

  salaWidget->setLayout(salaLayout);
  salaWidget->hide();

  tipologia->insertItem(0, "Singolo");
  tipologia->insertItem(1, "Abbonamento");

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

void Biglietto_View::showSearch() { widgetSing->show(); }

void Biglietto_View::resizeMe() { adjustSize(); }

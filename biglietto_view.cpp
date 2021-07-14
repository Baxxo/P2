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
      searchBtn(new QPushButton("ok")), salaLayout(new QVBoxLayout), postiOccupati(nullptr),
      nomeSala(nullptr), posti(nullptr), colonneMax(nullptr)
{

  tipologia->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  compraBiglietto->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  tipologiaBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  widgetSing->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  listaFilm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  search->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  searchBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  compraLayout->addWidget(listaFilm, Qt::AlignTop);
  compraLayout->addWidget(compraBiglietto, Qt::AlignBottom);

  layoutTipologia->addWidget(tipologia, Qt::AlignCenter);
  layoutTipologia->addWidget(tipologiaBtn, Qt::AlignCenter);

  mainLayout->addLayout(layoutTipologia, 0, 0, Qt::AlignCenter);
  mainLayout->addLayout(compraLayout, 1, 1, Qt::AlignCenter);

  utenteBigl->addWidget(search, Qt::AlignCenter);
  utenteBigl->addWidget(searchBtn, Qt::AlignCenter);

  mainWidget->setLayout(mainLayout);
  mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  widgetSing->setLayout(utenteBigl);

  tipologia->insertItem(0, "Singolo");
  tipologia->insertItem(1, "Abbonamento");

  connect(tipologiaBtn, SIGNAL(clicked()), this, SLOT(showSearch()));
  connect(searchBtn, SIGNAL(clicked()), controller, SLOT(stpBigl()));
  connect(listaFilm, SIGNAL(itemClicked(QListWidgetItem*)), controller, SLOT(showSala()));
  connect(listaFilm, SIGNAL(itemClicked(QListWidgetItem*)), controller, SLOT(setPostiOccupati()));

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

void Biglietto_View::getSalaView() {

    connect(posti, SIGNAL(cellClicked(int, int)), controller, SLOT(newPostoOccupato()));
    salaWidget->show(); }

void Biglietto_View::addFilminList(QString s)
{
    QListWidgetItem *item = new QListWidgetItem(s);
    listaFilm->addItem(item);
}

int Biglietto_View::getCurrentColumn(){ return posti->currentColumn(); }

int Biglietto_View::getCurrentRow(){ return posti->currentRow(); }

QString Biglietto_View::getNomeSala()
{
    return nomeSala->text();
}

QString Biglietto_View::getSelectedFilm(){ return listaFilm->currentItem()->text(); }

int Biglietto_View::getColonneMax()
{
    return colonneMax->text().toInt();
}

void Biglietto_View::setPostoOccupato(int r, int c)
{
    QTableWidgetItem* item= new QTableWidgetItem("occupato");
    item->setBackgroundColor("red");
    posti->setItem(r, c, item);
}

void Biglietto_View::createSalaView(int r, int c, QString f)
{
    if(posti){
        delete posti;
    }
    if(nomeSala){
        delete nomeSala;
    }


    salaWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    posti= new QTableWidget (r, c);
    nomeSala= new QLabel;
    colonneMax= new QLabel;
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

void Biglietto_View::showSearch() { widgetSing->show(); }

void Biglietto_View::resizeMe() { adjustSize(); }



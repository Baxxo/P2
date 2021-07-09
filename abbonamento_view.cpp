#include "abbonamento_view.h"
#include <QDebug>
#include "controller.h"

Abbonamento_view::Abbonamento_view(Controller *c, QWidget *parent)
    : QWidget(parent),
      controller(c),
      mainLayout(new QVBoxLayout),
      tipoAbbonamento(new QGroupBox),
      layoutRadio(new QHBoxLayout),
      abbonamento(new QRadioButton("Abbonamento")),
      abbonamentoFamigliare(new QRadioButton("Abbonamento Famigliare")),
      tipoLista(new QLabel("Lista utenti\nSeleziona solo un utente")),
      listaUtenti(new QListWidget),
      listaFamiglie(new QListWidget),
      aggiungi(new QPushButton("Aggiungi")),
      isUtente(true),
      alreadySelectedUt(false),
      alreadySelectedFm(false) {
  tipoLista->setAlignment(Qt::AlignHCenter);
  tipoLista->setProperty("class", "big_text");

  listaFamiglie->setProperty("class", "colorSelect");

  abbonamento->setChecked(true);
  layoutRadio->addWidget(abbonamento);
  layoutRadio->addWidget(abbonamentoFamigliare);
  tipoAbbonamento->setLayout(layoutRadio);

  mainLayout->addWidget(tipoAbbonamento);

  mainLayout->addWidget(tipoLista);
  mainLayout->addWidget(listaUtenti);
  mainLayout->addWidget(listaFamiglie);
  mainLayout->addWidget(aggiungi, Qt::AlignHCenter);
  listaFamiglie->hide();
  aggiungi->hide();

  setLayout(mainLayout);

  connect(abbonamento, SIGNAL(clicked()), this, SLOT(showAbbonamento()));
  connect(abbonamentoFamigliare, SIGNAL(clicked()), this,
          SLOT(showAbbFamiglaire()));

  connect(aggiungi, SIGNAL(clicked()), this, SLOT(addToAbbonamento()));

  connect(listaUtenti, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(clickListUtenti(QListWidgetItem *)));

  connect(listaFamiglie, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(clickListFamiglie(QListWidgetItem *)));

  setStyle();
}

void Abbonamento_view::addUtente(const QString &s, const QString &cf) {
  QListWidgetItem *itemN = new QListWidgetItem();
  QLabelCF *widgetText = new QLabelCF(new QLabel(s), cf);

  listaUtenti->addItem(itemN);
  itemN->setSelected(false);
  listaUtenti->setItemWidget(itemN, widgetText);
}

void Abbonamento_view::addFamiglia(const QString &name) {
  QListWidgetItem *itemN = new QListWidgetItem();
  QLabel *widgetText = new QLabel(name);

  listaFamiglie->addItem(itemN);
  itemN->setSelected(false);
  listaFamiglie->setItemWidget(itemN, widgetText);
}

void Abbonamento_view::clearListUtenti() { listaUtenti->clear(); }

void Abbonamento_view::clearListFamiglie() { listaFamiglie->clear(); }

void Abbonamento_view::setStyle() {
  QFile file(":/qss/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
}

void Abbonamento_view::showAbbonamento() {
  listaFamiglie->hide();
  listaUtenti->show();
  isUtente = false;
  tipoLista->setText(QString("Lista utenti\nSeleziona solo un utente"));
  if (!alreadySelectedUt)
    aggiungi->hide();
  else
    aggiungi->show();
  resizeMe();
}

void Abbonamento_view::showAbbFamiglaire() {
  listaUtenti->hide();
  listaFamiglie->show();
  isUtente = true;
  tipoLista->setText(QString("Lista Famiglie\nSeleziona solo una famiglia"));
  if (!alreadySelectedFm)
    aggiungi->hide();
  else
    aggiungi->show();
  resizeMe();
}

void Abbonamento_view::resizeMe() { adjustSize(); }

void Abbonamento_view::clickListUtenti(QListWidgetItem *item) {
  QLabelCF *lbl = dynamic_cast<QLabelCF *>(listaUtenti->itemWidget(item));

  if (!lbl->isSelected()) {
    if (!alreadySelectedUt) {
      lbl->setStyleSheet("QLabel { background-color : LightGreen;}");
      lbl->setSelect(true);
      aggiungi->show();
      alreadySelectedUt = true;
    }
  } else {
    lbl->setStyleSheet("QLabel { background-color : #00A2E8;}");
    lbl->setSelect(false);
    alreadySelectedUt = false;
    aggiungi->hide();
  }
  listaUtenti->setItemWidget(item, lbl);
  resizeMe();
}

void Abbonamento_view::clickListFamiglie(QListWidgetItem *item) {
  QLabel *lbl = dynamic_cast<QLabel *>(listaFamiglie->itemWidget(item));

  if (!alreadySelectedFm) {
    lbl->setStyleSheet("QLabel { background-color : LightGreen;}");
    aggiungi->show();
    alreadySelectedFm = true;

  } else {
    lbl->setStyleSheet("QLabel { background-color : #00A2E8;}");
    alreadySelectedFm = false;
    aggiungi->hide();
  }
  listaFamiglie->setItemWidget(item, lbl);
  resizeMe();
}

void Abbonamento_view::addToAbbonamento() {
  if (isUtente) {
    QListWidgetItem *item = listaUtenti->currentItem();
    QLabelCF *lbl = dynamic_cast<QLabelCF *>(listaUtenti->itemWidget(item));
    if (addUtenteAbb(lbl->getCf())) {
      qDebug() << "inserito";
    }
  } else {
    // addFamigliaAbb(item);
  }
}

bool Abbonamento_view::addUtenteAbb(const QString &cf) {
  return controller->addUsertToAbb(cf);
}

bool Abbonamento_view::addFamigliaAbb(QListWidgetItem *item) {}

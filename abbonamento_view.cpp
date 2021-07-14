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
      utentiLabel(new QLabel("Lista utenti\nSeleziona solo un utente")),
      listaUtenti(new QListWidget),
      famiglieLabel(new QLabel("Lista Famiglie\nSeleziona una sola famiglia")),
      listaFamiglie(new QListWidget),
      aggiungi(new QPushButton("Aggiungi")),
      labelUtility(new QLabel()),
      currentUser(nullptr),
      currentfamily(nullptr),
      isUtente(true),
      alreadySelectedUt(false),
      alreadySelectedFm(false) {
  utentiLabel->setAlignment(Qt::AlignHCenter);
  utentiLabel->setProperty("class", "big_text");

  famiglieLabel->setAlignment(Qt::AlignHCenter);
  famiglieLabel->setProperty("class", "big_text");

  labelUtility->setAlignment(Qt::AlignHCenter);
  labelUtility->setProperty("class", "succes");

  // listaFamiglie->setProperty("class", "colorSelect");

  abbonamento->setChecked(true);
  layoutRadio->addWidget(abbonamento);
  layoutRadio->addWidget(abbonamentoFamigliare);
  tipoAbbonamento->setLayout(layoutRadio);

  mainLayout->addWidget(tipoAbbonamento);

  mainLayout->addWidget(utentiLabel);
  mainLayout->addWidget(listaUtenti);
  mainLayout->addWidget(famiglieLabel);
  mainLayout->addWidget(listaFamiglie);
  mainLayout->addWidget(aggiungi, Qt::AlignHCenter);
  mainLayout->addWidget(labelUtility);
  listaFamiglie->hide();
  famiglieLabel->hide();
  aggiungi->hide();

  setLayout(mainLayout);

  connect(abbonamento, SIGNAL(clicked()), this, SLOT(showAbbonamento()));
  connect(abbonamentoFamigliare, SIGNAL(clicked()), this,
          SLOT(showAbbFamiglaire()));

  connect(listaUtenti, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(clickListUtenti(QListWidgetItem *)));

  connect(listaFamiglie, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(clickListFamiglie(QListWidgetItem *)));

  connect(aggiungi, SIGNAL(clicked()), this, SLOT(createAbbonamento()));
  // connect(aggiungi, SIGNAL(clicked()), listaUtenti, SLOT(clearSelection()));
  // connect(aggiungi, SIGNAL(clicked()), listaFamiglie,
  // SLOT(clearSelection()));

  setStyle();

  setWindowTitle(QString("Creazione abbonamenti"));
}

void Abbonamento_view::resizeMe() { adjustSize(); }

void Abbonamento_view::setStyle() {
  QFile file(":/qss/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
}

void Abbonamento_view::addUtente(const QString &s, const QString &cf) {
  QListWidgetItem *itemN = new QListWidgetItem();
  QLabelCF *widgetText = new QLabelCF(new QLabel(s), cf);

  listaUtenti->addItem(itemN);
  itemN->setSelected(false);
  listaUtenti->setItemWidget(itemN, widgetText);
}

void Abbonamento_view::addFamiglia(const QString &s, const QString &name) {
  QListWidgetItem *itemN = new QListWidgetItem();
  QLabelCF *widgetText = new QLabelCF(new QLabel(s), name);

  listaFamiglie->addItem(itemN);
  itemN->setSelected(false);
  listaFamiglie->setItemWidget(itemN, widgetText);
}

void Abbonamento_view::clearListUtenti() { listaUtenti->clear(); }

void Abbonamento_view::clearListFamiglie() { listaFamiglie->clear(); }

void Abbonamento_view::showAbbonamento() {
  famiglieLabel->hide();
  listaFamiglie->hide();
  isUtente = true;
  if (!alreadySelectedUt)
    aggiungi->hide();
  else {
    if (currentUser) listaUtenti->setCurrentItem(currentUser);
    aggiungi->show();
  }
  resizeMe();
}

void Abbonamento_view::showAbbFamiglaire() {
  famiglieLabel->show();
  listaFamiglie->show();
  isUtente = false;
  if (!alreadySelectedFm || !alreadySelectedUt)
    aggiungi->hide();
  else {
    if (currentUser) listaUtenti->setCurrentItem(currentUser);
    if (currentfamily) listaFamiglie->setCurrentItem(currentfamily);
    aggiungi->show();
  }
  resizeMe();
}

void Abbonamento_view::clickListUtenti(QListWidgetItem *item) {
  currentUser = item;
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
  currentfamily = item;
  QLabelCF *lbl = dynamic_cast<QLabelCF *>(listaFamiglie->itemWidget(item));

  if (!lbl->isSelected()) {
    if (!alreadySelectedFm) {
      lbl->setStyleSheet("QLabel { background-color : LightGreen;}");
      lbl->setSelect(true);
      if (alreadySelectedUt) aggiungi->show();
      alreadySelectedFm = true;
    }
  } else {
    lbl->setStyleSheet("QLabel { background-color : #00A2E8;}");
    lbl->setSelect(false);
    alreadySelectedFm = false;
    aggiungi->hide();
  }
  listaUtenti->setItemWidget(item, lbl);
  resizeMe();
}

void Abbonamento_view::createAbbonamento() {
  QListWidgetItem *item = listaUtenti->currentItem();
  QLabelCF *lbl = dynamic_cast<QLabelCF *>(listaUtenti->itemWidget(item));
  QLabelCF *lblFam = nullptr;
  QListWidgetItem *itemFam = nullptr;

  if (isUtente) {
    if (addAbbonamentoToController(lbl->getCf())) {
      labelUtility->setStyleSheet("QLabel { color : LightGreen;}");
      labelUtility->setText("Abbonamento creato correttamente");
    } else {
      labelUtility->setStyleSheet("QLabel { color : Red;}");
      labelUtility->setText("Errore nella crezione dell' abbonamento");
    }
  } else {
    itemFam = listaFamiglie->currentItem();
    lblFam = dynamic_cast<QLabelCF *>(listaFamiglie->itemWidget(itemFam));
    if (addAbbonamentoFamToController(lblFam->getCf(), lbl->getCf())) {
      labelUtility->setStyleSheet("QLabel { color : LightGreen;}");
      labelUtility->setText("Abbonamento famigliare creato correttamente");
    } else {
      labelUtility->setStyleSheet("QLabel { color : Red;}");
      labelUtility->setText(
          "Errore nella crezione dell' abbonamento famigliare");
    }
    alreadySelectedFm = false;
  }
  alreadySelectedUt = false;
  aggiungi->hide();

  lbl->setStyleSheet("QLabel { background-color : #00A2E8;}");
  lbl->setSelect(false);
  listaUtenti->setItemWidget(item, lbl);

  if (lblFam && itemFam) {
    lblFam->setStyleSheet("QLabel { background-color : #00A2E8;}");
    lblFam->setSelect(false);
    listaFamiglie->setItemWidget(itemFam, lblFam);
  }
}

bool Abbonamento_view::addAbbonamentoToController(const QString &cf) {
  return controller->createAbbonamento(cf);
}

bool Abbonamento_view::addAbbonamentoFamToController(const QString &name,
                                                     const QString &cf) {
  return controller->createAbbonamentoFamigliare(name, cf);
}

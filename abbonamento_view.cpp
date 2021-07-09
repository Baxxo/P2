#include "abbonamento_view.h"
#include <QDebug>

Abbonamento_view::Abbonamento_view(Controller *c, QWidget *parent)
    : QWidget(parent),
      controller(c),
      mainLayout(new QVBoxLayout),
      tipoAbbonamento(new QGroupBox),
      layoutRadio(new QHBoxLayout),
      abbonamento(new QRadioButton("Abbonamento")),
      abbonamentoFamigliare(new QRadioButton("Abbonamento Famigliare")),
      tipoLista(new QLabel("Lista utenti")),
      listaUtenti(new QListWidget),
      listaFamiglie(new QListWidget),
      aggiungi(new QPushButton("Aggiugni")),
      isUtente(true) {
  tipoLista->setAlignment(Qt::AlignHCenter);
  tipoLista->setProperty("class", "big_text");

  abbonamento->setChecked(true);
  layoutRadio->addWidget(abbonamento);
  layoutRadio->addWidget(abbonamentoFamigliare);
  tipoAbbonamento->setLayout(layoutRadio);

  mainLayout->addWidget(tipoAbbonamento);

  mainLayout->addWidget(tipoLista);
  mainLayout->addWidget(listaUtenti);
  mainLayout->addWidget(listaFamiglie);
  listaFamiglie->hide();

  setLayout(mainLayout);

  connect(abbonamento, SIGNAL(clicked()), this, SLOT(showAbbonamento()));
  connect(abbonamentoFamigliare, SIGNAL(clicked()), this,
          SLOT(showAbbFamiglaire()));

  connect(listaUtenti, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(addToAbbonamento(QListWidgetItem *)));
  connect(listaFamiglie, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(addToAbbonamento(QListWidgetItem *)));

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
  tipoLista->setText(QString("Lista utenti"));
  resizeMe();
}

void Abbonamento_view::showAbbFamiglaire() {
  listaUtenti->hide();
  listaFamiglie->show();
  isUtente = true;
  tipoLista->setText(QString("Lista Famiglie"));
  resizeMe();
}

void Abbonamento_view::resizeMe() { adjustSize(); }

void Abbonamento_view::addToAbbonamento(QListWidgetItem *item) {
  if (isUtente) {
    QLabelCF *lbl = dynamic_cast<QLabelCF *>(listaUtenti->itemWidget(item));
    if (!lbl->isSelected()) {
      if (true) {
        lbl->setStyleSheet("QLabel { background-color : LightGreen;}");
        lbl->setSelect(true);
      }
    } else {
      lbl->setStyleSheet("QLabel { background-color : #00A2E8;}");
      lbl->setSelect(false);
    }
    // addUtenteAbb(item);

    listaUtenti->setItemWidget(item, lbl);
  } else {
    // addFamigliaAbb(item);
  }
}

void Abbonamento_view::addUtenteAbb(QListWidgetItem *item) {}

void Abbonamento_view::addFamigliaAbb(QListWidgetItem *item) {}

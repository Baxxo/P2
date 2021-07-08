#include "client.h"
#include "controller.h"

Client::Client(Controller *c, QWidget *parent)
    : QMainWindow(parent),
      mainLayout(new QGridLayout),
      nuovaFamiglia(new QPushButton("Crea nuova Famiglia")),
      nuovoAbbonamento(new QPushButton("Acqusita un Abbonamento")),
      nuovoBiglietto(new QPushButton("Acqusita un Biglietto")),
      btnLayout(new QVBoxLayout),
      widget(new QWidget(this)),
      label(new QLabel("Cliente")),
      controller(c) {
  label->setProperty("class", "title");
  nuovoUtente = new QPushButton("Crea Nuovo Utente");

  btnLayout->addWidget(label, Qt::AlignCenter);
  btnLayout->addWidget(nuovoUtente, Qt::AlignCenter);
  btnLayout->addWidget(nuovaFamiglia, Qt::AlignCenter);
  btnLayout->addWidget(nuovoAbbonamento, Qt::AlignCenter);
  btnLayout->addWidget(nuovoBiglietto, Qt::AlignCenter);

  mainLayout->addLayout(btnLayout, 0, 1, Qt::AlignCenter);
  widget->setLayout(mainLayout);

  setCentralWidget(widget);

  setWindowTitle(QString("Cliente"));

  resize(300, 300);
  setStyle();

  connect(nuovoUtente, SIGNAL(clicked()), controller, SLOT(openUtente()));
  connect(nuovaFamiglia, SIGNAL(clicked()), controller, SLOT(openFamiglia()));
  connect(nuovoAbbonamento, SIGNAL(clicked()), controller,
          SLOT(openAbbonamento()));
  connect(nuovoBiglietto, SIGNAL(clicked()), controller, SLOT(openBiglietto()));
}

void Client::setStyle() {
  QFile file(":/qss/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
}

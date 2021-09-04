#include "utente_View.h"
#include "controller.h"

Utente_View::Utente_View(Controller *c, QWidget *parent)
    : QWidget(parent),
      widget(new QWidget(this)),
      mainlayout(new QGridLayout),
      btnLayout(new QVBoxLayout),
      lineLayout(new QVBoxLayout),
      confermaBtn(new QPushButton("Conferma")),
      annullaBtn(new QPushButton("Annulla")),
      name(new QLineEditClickable()),
      surname(new QLineEditClickable()),
      CF(new QLineEditClickable()),
      age(new QLineEditClickable()),
      numtel(new QLineEditClickable()),
      conferma(new QLabel),
      desktop(new QDesktopWidget),
      controller(c) {
  setWindowTitle(QString("Creazione Utente"));

  CF->setValidator(new QRegularExpressionValidator(
      QRegularExpression("[a-zA-Z]{6}[0-9]{2}[abcdehlmprstABCDEHLMPRST]{1}["
                         "0-9]{2}([a-zA-Z]{1}[0-9]{3})[a-zA-Z]{1}")));
  name->setValidator(
      new QRegularExpressionValidator(QRegularExpression("[a-zA-Z]{12}")));
  surname->setValidator(
      new QRegularExpressionValidator(QRegularExpression("[a-zA-Z]{12}")));
  age->setValidator(
      new QRegularExpressionValidator(QRegularExpression("[0-9]{3}")));
  numtel->setValidator(
      new QRegularExpressionValidator(QRegularExpression("[0-9]{10}")));

  // layout bottoni
  btnLayout->addWidget(confermaBtn, Qt::AlignCenter);
  btnLayout->addWidget(annullaBtn, Qt::AlignCenter);
  mainlayout->addLayout(btnLayout, 1, 0, Qt::AlignCenter);

  // layout linee di testor
  lineLayout->addWidget(name, Qt::AlignCenter);
  lineLayout->addWidget(surname, Qt::AlignCenter);
  lineLayout->addWidget(CF, Qt::AlignCenter);
  lineLayout->addWidget(age, Qt::AlignCenter);
  lineLayout->addWidget(numtel, Qt::AlignCenter);
  lineLayout->addWidget(conferma);
  mainlayout->addLayout(lineLayout, 0, 0, Qt::AlignCenter);

  // layout widget, ottimizzazione finestra per il desktop
  widget->setLayout(mainlayout);

  resize(300, 300);
  move((desktop->width() - 300) / 2, (desktop->height() - 300) / 2);

  // inizializzazione default delle linee di testo
  name->setText("Name");
  surname->setText("Surname");
  CF->setText("Codice Fiscale");
  age->setText("Età");
  numtel->setText("Numero di telefono");

  setStyle();

  // connessioni al controller
  connect(confermaBtn, SIGNAL(clicked()), controller, SLOT(salvaUtente()));
  connect(annullaBtn, SIGNAL(clicked()), this, SLOT(annullaUtente()));
}

void Utente_View::annullaUtente() { close(); }

void Utente_View::setStyle() {
  QFile file(":/qss/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
}

QString Utente_View::getName() const { return name->text(); }

QString Utente_View::getSurname() const { return surname->text(); }

QString Utente_View::getCF() const { return CF->text(); }

QString Utente_View::getAge() const { return age->text(); }

QString Utente_View::getNumTel() const { return numtel->text(); }

void Utente_View::setConferma(const QString &c) { conferma->setText(c); }

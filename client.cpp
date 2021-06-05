#include "client.h"
#include "controller.h"

Client::Client(Controller *c, QWidget *parent) : QMainWindow(parent), controller(c)
{
  label = new QLabel("Cliente");
  label->setProperty("class", "title");
  nuovoUtente= new QPushButton("Crea Nuovo Utente");
  nuovaFamiglia= new QPushButton("Crea nuova Famiglia");
  mainLayout=new QGridLayout;
  widget=new QWidget(this);

  btnLayout=new QVBoxLayout;
  btnLayout->addWidget(label, Qt::AlignCenter);
  btnLayout->addWidget(nuovoUtente, Qt::AlignCenter);
  btnLayout->addWidget(nuovaFamiglia, Qt::AlignCenter);

  mainLayout->addLayout(btnLayout, 0, 1, Qt::AlignCenter);
  widget->setLayout(mainLayout);

  setCentralWidget(widget);

  setWindowTitle(QString("Cliente"));

  resize(300,300);
  setStyle();

  connect(nuovoUtente, SIGNAL(clicked()), controller, SLOT(openUtente()));
  connect(nuovaFamiglia, SIGNAL(clicked()), controller, SLOT(openFamiglia()));

}

void Client::setStyle()
{
    QFile file(":/qss/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    setStyleSheet(styleSheet);
}

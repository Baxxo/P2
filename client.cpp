#include "client.h"
#include "controller.h"

Client::Client(QWidget *parent) : QMainWindow(parent)
{
  nuovoUtente= new QPushButton("Crea Nuovo Utente");
  mainLayout=new QGridLayout;
  widget=new QWidget(this);
  btnLayout=new QHBoxLayout;

  setCentralWidget(widget);
  btnLayout->addWidget(nuovoUtente, Qt::AlignCenter);
  mainLayout->addLayout(btnLayout, 0, 1, Qt::AlignCenter);
  widget->setLayout(mainLayout);
  controller= new Controller;
  desktop = QApplication::desktop();


  resize(300,300);
  setStyle();



  connect(nuovoUtente, SIGNAL(clicked()), controller, SLOT(openUtente()));


}

void Client::setStyle()
{
    QFile file(":/qss/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    setStyleSheet(styleSheet);
}

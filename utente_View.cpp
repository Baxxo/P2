#include "utente_View.h"
#include "controller.h"

Utente_View::Utente_View(Controller *c, QWidget *parent) : controller(c), QWidget(parent)
{
    //dichiarazione dei parametri
    mainlayout= new QGridLayout;
    btnLayout= new QVBoxLayout;
    lineLayout= new QVBoxLayout;
    widget= new QWidget(this);
    confermaBtn= new QPushButton("Conferma");
    annullaBtn= new QPushButton("Annulla");
    name= new QLineEdit();
    CF= new QLineEdit();
    age= new QLineEdit();
    numtel= new QLineEdit();

    //layout bottoni
    btnLayout->addWidget(confermaBtn, Qt::AlignCenter);
    btnLayout->addWidget(annullaBtn, Qt::AlignCenter);
    mainlayout->addLayout(btnLayout,1,0,Qt::AlignCenter);


    //layout linee di testo
    lineLayout->addWidget(name, Qt::AlignCenter);
    lineLayout->addWidget(CF, Qt::AlignCenter);
    lineLayout->addWidget(age, Qt::AlignCenter);
    lineLayout->addWidget(numtel, Qt::AlignCenter);
    mainlayout->addLayout(lineLayout,0,0,Qt::AlignCenter);

    //layout widget, ottimizzazione finestra per il desktop
    widget->setLayout(mainlayout);
    desktop = new QDesktopWidget;
    resize(300,300);
    move((desktop->width()-300)/2,(desktop->height()-300)/2);

    //inizializzazione default delle linee di testo
    name->setText("Name");
    CF->setText("Codice Fiscale");
    age->setText("Età");
    numtel->setText("Numero di telefono");

    setStyle();

    //connessioni al controller
    connect(confermaBtn, SIGNAL(clicked()), controller, SLOT(salvaUtente()));
    connect(annullaBtn, SIGNAL(clicked()), controller, SLOT(annullaUtente()));




}
void Utente_View::setStyle()
{
  QFile style(":/qss/style.css");
  style.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(style.readAll());

  setStyleSheet(styleSheet);
}

QString Utente_View::getName()
{
    return name->text();
}

QString Utente_View::getCF()
{
    return CF->text();
}

QString Utente_View::getAge()
{
    return age->text();
}

QString Utente_View::getNumTel()
{
    return numtel->text();
}



/*void Utente_View::read() {
  QString settings;
  QFile file(QDir::homePath() + "/Desktop/P2-feature-MainWindow/json/test.json");

  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "File open error";
  } else {

    settings = file.readAll();

    QJsonDocument doc(QJsonDocument::fromJson(settings.toUtf8()));
    QJsonObject jObj = doc.object();

    QString txt = jObj["name"].toString() + " " + QString::number(jObj["age"].toInt()) + ";";
    qDebug() << "Age: " << jObj["age"].toInt();

  }
  file.close();

}*/








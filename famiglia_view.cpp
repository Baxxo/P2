#include "famiglia_view.h"
#include "controller.h"

Famiglia_View::Famiglia_View(Controller* c, QWidget *parent) : QWidget(parent), controller(c)
{
    widget= new QWidget(this);
    menuLayout= new QVBoxLayout;
    btnLayout= new QVBoxLayout;
    mainlayout=new QGridLayout;
    search= new QLineEdit;
    familyName= new QLineEdit;
    listaFamily= new QListWidget;
    saveFamily= new QPushButton("Salva Famiglia");
    aggiorna= new QPushButton("Search");

    search->setText("Type in a CF and press search");
    familyName->setText("Type in a family name");
    menuLayout->addWidget(listaFamily, Qt::AlignRight);
    menuLayout->addWidget(search, Qt::AlignCenter);
    menuLayout->addWidget(familyName, Qt::AlignCenter);
    btnLayout->addWidget(aggiorna, Qt::AlignCenter);
    btnLayout->addWidget(saveFamily, Qt::AlignCenter);
    mainlayout->addLayout(menuLayout, 0,0, Qt::AlignCenter);
    mainlayout->addLayout(btnLayout, 1, 0, Qt::AlignCenter);
    widget->setLayout(mainlayout);

    desktop = QApplication::desktop();
    int _size = desktop->height()*0.2;
    resize(_size,_size);

    setStyle();

    connect(aggiorna, SIGNAL(clicked()), controller, SLOT(listaUtenti()));
    connect(saveFamily, SIGNAL(clicked()), controller, SLOT(salvaFamiglia()));
    //connect(menu, SIGNAL(currentIndexChanged()), this, SLOT(signaltest()));
}

void Famiglia_View::addLista(QString m)
{
    listaFamily->addItem(m);
}

//void Famiglia_View::showMenu()
//{
//    menu->show();
//    //qDebug() << "lmao";
//}

void Famiglia_View::setStyle()
{
    QFile style(":/qss/style.css");
    style.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(style.readAll());

    setStyleSheet(styleSheet);
}

QString Famiglia_View::getItem(int i)
{
    return listaFamily->item(i)->text();
}

QString Famiglia_View::getSearch()
{
    return search->text();
}

int Famiglia_View::getListSize()
{
    return listaFamily->count();
}

QString Famiglia_View::getFamilyName()
{
    return familyName->text();
}

void Famiglia_View::signaltest()
{
   qDebug() << "signal";
}

QString Famiglia_View::read() {
  QString settings;
  QFile file(controller->getPathJsonUtenti());

  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "File open error";
    QString error= "error";
    return error;
  } else {

    settings = file.readAll();

    QJsonDocument doc(QJsonDocument::fromJson(settings.toUtf8()));
    QJsonObject jObj = doc.object();

    QString txt = jObj["name"].toString(); //QString::number(jObj["age"].toInt()) + ";";

    qDebug() << "Name: " << jObj["name"].toString();
    return txt;
  }
  file.close();
  return "";
}

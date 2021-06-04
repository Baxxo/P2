#include "famiglia_view.h"
#include "controller.h"

#include <QTimer>

Famiglia_View::Famiglia_View(Controller* c, QWidget *parent) : QWidget(parent), controller(c)
{
    widget= new QWidget(this);
    menuLayout= new QVBoxLayout;
    btnLayout= new QVBoxLayout;
    mainlayout=new QGridLayout;
    search= new QLineEditClickable;
    familyName= new QLineEditClickable;
    listaUtenti= new QListWidget;
    saveFamily= new QPushButton("Salva Famiglia");
    aggiorna= new QPushButton("Search");

    setWindowTitle(QString("Creazione famiglia"));

    familyName->setText("Type in a family name");
    search->setText("Type in a CF and press search");
    menuLayout->addWidget(familyName, Qt::AlignCenter);
    menuLayout->addWidget(listaUtenti, Qt::AlignCenter);
    menuLayout->addWidget(search, Qt::AlignCenter);
    btnLayout->addWidget(aggiorna, Qt::AlignCenter);
    btnLayout->addWidget(saveFamily, Qt::AlignCenter);
    mainlayout->addLayout(menuLayout, 0,0, Qt::AlignCenter);
    mainlayout->addLayout(btnLayout, 1, 0, Qt::AlignCenter);
    widget->setLayout(mainlayout);

    setMinimumSize(320,370);

    QTimer::singleShot(0,this,SLOT(resizeMe()));

    setStyle();

    connect(aggiorna, SIGNAL(clicked()), controller, SLOT(listaUtenti()));
    connect(saveFamily, SIGNAL(clicked()), controller, SLOT(salvaFamiglia()));
    connect(familyName,SIGNAL(clicked()), this, SLOT(cleanTextFamily()));
    connect(search,SIGNAL(clicked()), this, SLOT(cleanTextSearch()));
}

void Famiglia_View::addUtenteToLista(const QString& text, const QString& cf)
{
    listaUtenti->addItem(new QLabelCF(new QLabel(text),cf));
}

void Famiglia_View::setStyle()
{
    QFile style(":/qss/style.css");
    style.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(style.readAll());

    setStyleSheet(styleSheet);
}

QString Famiglia_View::getItem(int i)
{
    return listaUtenti->item(i)->text();
}

QString Famiglia_View::getSearch()
{
    return search->text();
}

int Famiglia_View::getListSize()
{
    return listaUtenti->count();
}

QString Famiglia_View::getFamilyName()
{
    return familyName->text();
}

void Famiglia_View::clearList()
{
    listaUtenti->clear();
}

void Famiglia_View::signaltest()
{
    qDebug() << "signal";
}

void Famiglia_View::resizeMe()
{
    adjustSize();
}

void Famiglia_View::cleanTextFamily()
{
    if(familyName->text() == "Type in a family name") familyName->setText("");
}

void Famiglia_View::cleanTextSearch()
{
    if(search->text() == "Type in a CF and press search") search->setText("");
}

QString Famiglia_View::read() {
  QString settings;
  QFile file(controller->getPathJsonUsers());

  if (!file.open(QIODevice::ReadOnly)) {
    controller->openError("Error reading file");
    return QString("error");
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

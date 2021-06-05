#include "famiglia_view.h"
#include "controller.h"

#include <QTimer>

Famiglia_View::Famiglia_View(Controller* c, QWidget *parent) : QWidget(parent), controller(c)
{
    widget= new QWidget(this);
    widget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    menuLayout= new QVBoxLayout;
    btnLayout= new QVBoxLayout;
    mainlayout=new QGridLayout;
    search= new QLineEditClickable;
    familyName= new QLineEditClickable;
    listaUtenti= new QListWidget;
    labelListaUtenti = new QLabel("Utenti prenseti nel sistema");
    labelListaUtenti->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    saveFamily= new QPushButton("Salva Famiglia");
    saveFamily->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    aggiorna= new QPushButton("Search");
    aggiorna->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    layoutListUsers = new QVBoxLayout;

    setWindowTitle(QString("Creazione famiglia"));

    familyName->setText("Type in a family name");
    search->setText("Type in a CF and press search");
    menuLayout->addWidget(familyName, Qt::AlignCenter);
    menuLayout->addWidget(labelListaUtenti, Qt::AlignCenter);
    menuLayout->addWidget(listaUtenti, Qt::AlignCenter);
    menuLayout->addWidget(search, Qt::AlignCenter);
    btnLayout->addWidget(aggiorna, Qt::AlignCenter);
    btnLayout->addWidget(saveFamily, Qt::AlignCenter);
    mainlayout->addLayout(menuLayout, 0,0, Qt::AlignCenter);
    mainlayout->addLayout(btnLayout, 1, 0, Qt::AlignCenter);
    widget->setLayout(mainlayout);

    setMinimumSize(320,400);

    QTimer::singleShot(0,this,SLOT(resizeMe()));

    setStyle();

    connect(aggiorna, SIGNAL(clicked()), controller, SLOT(listaUtenti()));
    connect(saveFamily, SIGNAL(clicked()), controller, SLOT(salvaFamiglia()));
    connect(familyName,SIGNAL(clicked()), this, SLOT(cleanTextFamily()));
    connect(search,SIGNAL(clicked()), this, SLOT(cleanTextSearch()));
    connect(listaUtenti, SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(addUtenteToFamiglia(QListWidgetItem*)));
}

void Famiglia_View::addUtenteToLista(const QString& text, const QString& cf)
{
  QListWidgetItem* itemN = new QListWidgetItem();
  QLabelCF* widgetText = new QLabelCF(new QLabel(text),cf);

  listaUtenti->addItem(itemN);
  listaUtenti->setItemWidget(itemN,widgetText);

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

void Famiglia_View::addUtenteToFamiglia(QListWidgetItem* item)
{
  QLabelCF* lbl = dynamic_cast<QLabelCF*>(listaUtenti->itemWidget(item));
  lbl->setStyleSheet("QLabel { background-color : LightGreen; color : black; }");

  //qDebug() << lbl->getCf();
  listaUtenti->setItemWidget(item,lbl);
  controller->addUserToFamily(lbl->getCf());/*
  Famiglia& fam = *(controller->getFam());
  fam.addMembro(new Utente("test","tests",10,lbl->getCf().toStdString(),"1231231231"));

  for(unsigned int i=0;i<fam.getSize();i++){
      qDebug() << QString::fromUtf8(fam[i].getCodFisc().c_str());
    }
  qDebug() << "______________";*/

  //manca da cercare utente nel vector
}

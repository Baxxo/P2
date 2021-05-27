#include "famiglia_view.h"
#include "controller.h"

Famiglia_View::Famiglia_View(Controller* c, QWidget *parent) : QWidget(parent), controller(c)
{
    widget= new QWidget(this);
    menuLayout= new QVBoxLayout;
    btnLayout= new QVBoxLayout;
    mainlayout=new QGridLayout;
    menu=new QComboBox;
    listaFamily= new QComboBox;
    aggiorna= new QPushButton("Aggiorna");

    menuLayout->addWidget(menu, Qt::AlignLeft);
    menuLayout->addWidget(listaFamily, Qt::AlignRight);
    btnLayout->addWidget(aggiorna, Qt::AlignCenter);
    mainlayout->addLayout(menuLayout, 0,0, Qt::AlignCenter);
    mainlayout->addLayout(btnLayout, 1, 0, Qt::AlignCenter);
    menu->hide();
    widget->setLayout(mainlayout);

    desktop = QApplication::desktop();
    int _size = desktop->height()*0.2;
    resize(_size,_size);

    setStyle();

    connect(aggiorna, SIGNAL(clicked()), controller, SLOT(listaUtenti()));
    //connect(menu, SIGNAL(currentIndexChanged()), this, SLOT(signaltest()));
}

void Famiglia_View::setMenu(QComboBox *m)
{
    menu=m;
}

void Famiglia_View::showMenu()
{
    menu->show();
    //qDebug() << "lmao";
}

void Famiglia_View::setStyle()
{
    QFile style(":/qss/style.css");
    style.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(style.readAll());

    setStyleSheet(styleSheet);
}

void Famiglia_View::signaltest()
{
   qDebug() << "signal";
}

QString Famiglia_View::read() {
  QString settings;
  QFile file(controller->getPathJson());

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

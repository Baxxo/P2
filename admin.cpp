#include "admin.h"

Admin::Admin(Controller* c, QWidget * parent): controller(c), QMainWindow(parent), i(0) {

  baseLayout = new QGridLayout();
  mainLayout = new QVBoxLayout();

  QFont font;
  font.setPointSize(50);
  font.setBold(true);

  admin = new QLabel("Admin");
  admin->setFont(font);

  mainLayout->addWidget(admin,0,Qt::AlignCenter);
  mainLayout->addLayout(baseLayout);

  widget = new QWidget();
  widget -> setLayout(mainLayout);

  desktop = QApplication::desktop();
  font.setPointSize(15);

  labelAbb = new QLabel("Abbonamenti");
  labelAbb->setFont(font);
  listAbb = new QListWidget();

  labelFam = new QLabel("Famiglie");
  labelFam->setFont(font);
  listFam = new QListWidget();

  labelUt = new QLabel("Utenti");
  labelUt->setFont(font);
  listUt = new QListWidget();


  for (unsigned int j = 0; j < 50; ++j) {
      QString s = "testo " + QString::number(j+1);
      QListWidgetItem* item = new QListWidgetItem(s);
      listAbb->addItem(item);
       item = new QListWidgetItem(s);
      listFam->addItem(item);
    }

  connect(listAbb,SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(getClickAbb()));
  connect(listFam,SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(getClickFam()));
  connect(listUt,SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(getClickUt()));

  baseLayout->addWidget(labelAbb,0,0,Qt::AlignCenter);
  baseLayout->addWidget(labelUt,0,1,Qt::AlignCenter);
  baseLayout->addWidget(labelFam,0,2,Qt::AlignCenter);

  baseLayout->addWidget(listAbb,1,0);
  baseLayout->addWidget(listUt,1,1);
  baseLayout->addWidget(listFam,1,2);

  resize(1000, 400);

  setCentralWidget(widget);
}

void Admin::addUtente(QString s)
{
  QListWidgetItem* item = new QListWidgetItem(s);
  listUt->addItem(item);
}

void Admin::getClickAbb()
{
  qDebug() << "Abbonamento "<<listAbb->currentItem()->text();
}

void Admin::getClickFam()
{
  qDebug() << "Famiglia "<<listFam->currentItem()->text();
}

void Admin::getClickUt()
{
  qDebug() << "Utente "<<listUt->currentItem()->text();
}
/*
void Admin::read() {
  QFile file( QDir::currentPath()+ "/test.json" );
  qDebug() << QCoreApplication::applicationFilePath();

  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "File open error";
  } else {

    QString settings;
    settings = file.readAll();

    QJsonDocument doc(QJsonDocument::fromJson(settings.toUtf8()));
    QJsonObject jObj = doc.object();

    QString txt = jObj["name"].toString() + " " + QString::number(jObj["age"].toInt()) + ";";
    qDebug() << "Age: " << jObj["age"].toInt();

    //label -> setText(txt);

  }
  file.close();

}

void Admin::write() {
  QFile file( QDir::currentPath()+ "/test.json" );
  //QFile file(":/json/test.json");
     if (!file.open( QIODevice::WriteOnly )) {
         qDebug() << "Could not create Project File";
     }else{
         QJsonObject jsonObject;
         jsonObject.insert("name", "tom");
         jsonObject.insert("age", ++i);
         qDebug() << "i: " << i;

         QJsonDocument writeDoc;
         writeDoc.setObject(jsonObject);

         file.write(writeDoc.toJson());
     }
  file.close();
}*/

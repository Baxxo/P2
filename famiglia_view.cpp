#include "famiglia_view.h"

Famiglia_View::Famiglia_View(QWidget *parent) : QWidget(parent)
{
    mainlayout=new QVBoxLayout;
    menu=new QComboBox;
    mainlayout->addWidget(menu);
    setLayout(mainlayout);
    menu->addItem(read());
    menu->addItem("pappa");

}

QString Famiglia_View::read() {
  QString settings;
  QFile file(QDir::homePath() + "/Desktop/P2-feature-MainWindow/json/test.json");

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

}

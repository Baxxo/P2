#include "admin.h"

Admin::Admin(QWidget * parent): QMainWindow(parent), i(0) {
  label = new QLabel("Ciao da Admin");

  mainLayout = new QVBoxLayout();

  widget = new QWidget();
  widget -> setLayout(mainLayout);

  desktop = QApplication::desktop();

  readBtn = new QPushButton("READ");

  writeBtn = new QPushButton("WRITE");

  mainLayout -> addWidget(readBtn);
  mainLayout -> addWidget(writeBtn);
  mainLayout -> addWidget(label);

  connect(readBtn, SIGNAL(clicked()), this, SLOT(read()));
  connect(writeBtn, SIGNAL(clicked()), this, SLOT(write()));

  resize(300, 300);

  setCentralWidget(widget);
}

void Admin::read() {
  QString settings;
  QFile file(QDir::homePath() + "/QTheater/json/test.json");

  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "File open error";
  } else {

    settings = file.readAll();

    QJsonDocument doc(QJsonDocument::fromJson(settings.toUtf8()));
    QJsonObject jObj = doc.object();

    QString txt = jObj["name"].toString() + " " + QString::number(jObj["age"].toInt()) + ";";
    qDebug() << "Age: " << jObj["age"].toInt();

    label -> setText(txt);

  }
  file.close();

}

void Admin::write() {
  QFile file(QDir::homePath() + "/QTheater/json/test.json");

  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "File open error";
  } else {

    QJsonObject jsonObject;
    jsonObject.insert("name", "tom");
    jsonObject.insert("age", ++i);
    qDebug() << "i: " << i;

    QJsonDocument writeDoc;
    writeDoc.setObject(jsonObject);

    file.write(writeDoc.toJson());

  }
  file.close();
}

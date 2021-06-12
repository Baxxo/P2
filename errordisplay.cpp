#include "errordisplay.h"
#include <QFile>

ErrorDisplay::ErrorDisplay(QWidget *parent, QString errorMessage): QWidget(parent), mess(new QLabel(errorMessage))
{
  QFile file(":/qss/error.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);

  layout = new QVBoxLayout();

  layout->addWidget(mess,0,Qt::AlignCenter);
  setLayout(layout);

  resize(300,100);
}

void ErrorDisplay::setMessage(const QString &message)
{
  mess->setText(message);
}

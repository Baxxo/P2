#ifndef ERRORDISPLAY_H
#define ERRORDISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class ErrorDisplay: public QWidget
{
public:
  ErrorDisplay(QWidget *parent = nullptr, QString errorMessage = "");

  void setMessage(QString &message);

private:
  QLabel *mess;
  QVBoxLayout *layout;

};

#endif // ERRORDISPLAY_H

#ifndef UTENTE_VIEW_H
#define UTENTE_VIEW_H
#include "mainwindow.h"
#include "qlineeditclickable.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QDir>
#include <QFile>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QPushButton>
#include <QTextStream>
#include <QVBoxLayout>
#include <QWidget>

class Utente_View : public QWidget {
  Q_OBJECT

private:
  QWidget *widget;
  QGridLayout *mainlayout;
  QVBoxLayout *btnLayout;
  QVBoxLayout *lineLayout;
  QPushButton *confermaBtn;
  QPushButton *annullaBtn;
  QLineEditClickable *name;
  QLineEditClickable *surname;
  QLineEditClickable *CF;
  QLineEditClickable *age;
  QLineEditClickable *numtel;
  QDesktopWidget *desktop;
  Controller *controller;

public:
  Utente_View(Controller *c, QWidget *parent = nullptr);
  void setStyle();
  QString getName() const;
  QString getSurname() const;
  QString getCF() const;
  QString getAge() const;
  QString getNumTel() const;
};

#endif // UTENTE_VIEW_H

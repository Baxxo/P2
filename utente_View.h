#ifndef UTENTE_VIEW_H
#define UTENTE_VIEW_H
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
#include "mainwindow.h"
#include "qlineeditclickable.h"

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
  QLabel *conferma;
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
  void setConferma(const QString &c);
};

#endif  // UTENTE_VIEW_H

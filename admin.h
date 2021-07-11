#ifndef ADMIN_H
#define ADMIN_H

#include <QApplication>
#include <QCloseEvent>
#include <QDebug>
#include <QDesktopWidget>
#include <QDir>
#include <QFile>
#include <QGridLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QListView>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTextStream>
#include <QVBoxLayout>
#include <QWidget>

#include "mainwindow.h"
#include "qlabelcf.h"
#include "qlineeditclickable.h"

// using std::cout;
// using std::endl;

class Admin : public QMainWindow {
  Q_OBJECT
 public:
  Admin(Controller *c, MainWindow *parent = nullptr);
  ~Admin() = default;

  void setAbbonamenti();
  void addUtente(const QString &s);
  void addFamiglia(const QString &s);
  void addEntrata(const QString &s, const QString &cod);
  void setFamiglie();

  void clearListUtenti();
  void clearListFamiglie();
  void clearListEntrate();

  void setIsAdmin(bool b);

  QString getNomeFilm();
  QString getColonneSala();
  QString getRigheSala();
  QString getNomeSala();
  QString getSalaFilm();

 private slots:
  void getClickAbb();
  void getClickUt();
  void getClickFam();
  void getClickFilm();
  void addFilmLayout();
  void addSalaLayout();

 private:
  QDesktopWidget *desktop;
  QGridLayout *baseLayout;
  QVBoxLayout *mainLayout;

  MainWindow *p;

  QLabel *admin;

  QListWidget *listAbb;
  QListWidget *listUt;
  QListWidget *listFam;
  QListWidget *listFilm;
  QListWidget *listSala;

  QLabel *labelAbb;
  QLabel *labelUt;
  QLabel *labelFam;
  QLabel *labelFilm;
  QLabel *labelSala;

  QWidget *widget;

  QPushButton *addFilm;
  QPushButton *addSala;

  QWidget *widgetFilm;
  QGridLayout *filmLayout;
  QLineEditClickable *nomeFilm;
  QLineEditClickable *salaFilm;
  QPushButton *saveFilm;

  QWidget *widgetSala;
  QGridLayout *salaLayout;
  QLineEditClickable *nomeSala;
  QLineEditClickable *righeSala;
  QLineEditClickable *colonneSala;
  QPushButton *saveSala;

  Controller *controller;

  void closeEvent(QCloseEvent *event);
};

#endif  // ADMIN_H

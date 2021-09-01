#ifndef ADMIN_H
#define ADMIN_H

#include <QApplication>
#include <QCloseEvent>
#include <QComboBox>
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

  QLabel *utility;

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
  QComboBox *regola;

  Controller *controller;

  void closeEvent(QCloseEvent *event);

 private slots:
  void getClickAbb();
  void addFilmLayout();
  void addSalaLayout();

 public:
  Admin(Controller *c, MainWindow *parent = nullptr);
  ~Admin() = default;

  void setAbbonamenti();
  void addUtenteinList(const QString &s);
  void addFamigliainList(const QString &s);
  void addEntrata(const QString &s, const QString &cod);
  void addAbbonamento(const QString &s, const QString &cod);
  void setFamiglie();
  void addFilminList(const QString &s);
  void addSaleinList(const QString &s);

  void clearListEntrate();
  void clearListUtenti();
  void clearListFamiglie();
  void clearListAbbonamenti();

  void clearListFilm();
  void clearListSale();

  void setIsAdmin(bool b);

  QString getNomeFilm();
  QString getColonneSala();
  QString getRigheSala();
  QString getNomeSala();
  QString getSalaFilm();
  QString getRegola();
};

#endif  // ADMIN_H

#ifndef ADMIN_H
#define ADMIN_H

#include <QLabel>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTextStream>
#include <QListView>
#include <QListWidget>
#include <QDebug>
#include <QDir>
#include <QCloseEvent>

#include "mainwindow.h"


//using std::cout;
//using std::endl;

class Admin : public QMainWindow
{
  Q_OBJECT
public:
  Admin(Controller* c, MainWindow *parent = nullptr);
  ~Admin() = default;

  void setAbbonamenti();
  void addUtente(QString s);
  void addFamiglia(QString s);
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
  QDesktopWidget* desktop;
  QGridLayout* baseLayout;
  QVBoxLayout* mainLayout;

  MainWindow* p;

  QLabel* admin;

  QListWidget* listAbb;
  QListWidget* listUt;
  QListWidget* listFam;
  QListWidget* listFilm;
  QListWidget* listSala;

  QLabel* labelAbb;
  QLabel* labelUt;
  QLabel* labelFam;
  QLabel* labelFilm;
  QLabel* labelSala;
  QWidget* widget;

  QPushButton* addFilm;
  QPushButton* addSala;

  QWidget* widgetFilm;
  QGridLayout* filmLayout;
  QLineEdit* nomeFilm;
  QLineEdit* salaFilm;
  QPushButton* saveFilm;

  QWidget* widgetSala;
  QGridLayout* salaLayout;
  QLineEdit* nomeSala;
  QLineEdit* righeSala;
  QLineEdit* colonneSala;
  QPushButton* saveSala;

  Controller* controller;

  void closeEvent(QCloseEvent *event);
};

#endif // ADMIN_H

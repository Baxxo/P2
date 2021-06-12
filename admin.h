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

private slots:
  void getClickAbb();
  void getClickUt();
  void getClickFam();

private:
  QDesktopWidget* desktop;
  QGridLayout* baseLayout;
  QVBoxLayout* mainLayout;

  MainWindow* p;

  QLabel* admin;

  QListWidget* listAbb;
  QListWidget* listUt;
  QListWidget* listFam;

  QLabel* labelAbb;
  QLabel* labelUt;
  QLabel* labelFam;
  QWidget* widget;

  QPushButton* readBtn;
  QPushButton* writeBtn;

  Controller* controller;

  int i;

  void closeEvent(QCloseEvent *event);
};

#endif // ADMIN_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QDesktopWidget>
#include <QWidget>
#include <QFile>
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>

//#include <iostream>

class Controller;

//using std::cout;


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow() = default;

  MainWindow* getMainwindow();

  void setController(Controller *c);

  void changeTitleChooseUtenti(const QString &s);
  void changeTitleChooseFamiglie(const QString &s);
  void changeTitleChooseEntrata(const QString &s);
  void changeTitleAdmin(const QString &s);
  void setIsAdmin(bool b);

  void setLabelPathUser(const QString &s);
  void setLabelPathFamiglie(const QString &s);
  void setLabelPathEntrata(const QString &s);

private slots:

  void changeMenuSlot();

private:
  QDesktopWidget* desktop;

  QWidget* widget;

  QGridLayout* mainLayout;
  QVBoxLayout* v_layout;
  QGridLayout* buttonLayout;

  QLabel* title;

  QPushButton* changeBtn;

  QPushButton *chooseUtenti;
  QPushButton* chooseFamiglie;
  QPushButton* chooseEntrata;

  QPushButton* adminBtn;
  QPushButton* clientBtn;

  QLabel *pathUser;
  QLabel *pathFamilies;
  QLabel *pathEntrata;

  Controller* controller;

  void setStyle();
  void changeMenu();
  void setSlot();

  bool isVisReadBtn;

  void createLayoutAdCl();
  void destroyLayoutAdCl();
  void createLayoutSetup();
  void destroyLayoutSetup();

  QString prevAdmin;
  QString prevChooseUtenti;
  QString prevChooseFamiglie;
  QString prevChooseEntrata;

};
#endif // MAINWINDOW_H

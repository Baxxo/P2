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

  void setController(Controller*c);

private slots:

  void changeMenuSlot();

private:
  QDesktopWidget* desktop;

  QWidget* widget;

  QGridLayout* mainLayout;
  QVBoxLayout* v_layout;
  QVBoxLayout* buttonLayout;

  QLabel* title;

  QPushButton* changeBtn;

  QPushButton *chooseUtenti;
  QPushButton* chooseFamiglie;
  QPushButton* chooseEntrata;

  QPushButton* adminBtn;
  QPushButton* clientBtn;

  Controller* controller;

  void setStyle();
  void changeMenu();
  void setSlot();

  bool isVisReadBtn;

  void createLayoutAdCl(bool createNew);
  void destroyLayoutAdCl();
  void createLayoutSetup(bool createNew);
  void destroyLayoutSetup();


};
#endif // MAINWINDOW_H

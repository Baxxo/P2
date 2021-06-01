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
  void changeMenu();

private slots:



private:
  QDesktopWidget* desktop;

  QWidget* widget;

  QGridLayout* mainLayout;
  QVBoxLayout* v_layout;
  QVBoxLayout* buttonLayout;

  QLabel* title;
  QPushButton *chooseUtenti;
  QPushButton* chooseFamiglie;
  QPushButton* chooseEntrata;
  QPushButton* adminBtn;
  QPushButton* clientBtn;

  Controller* controller;

  void setStyle();

};
#endif // MAINWINDOW_H

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

#include <iostream>

class Controller;

using std::cout;

#include <QMainWindow>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  void setController(Controller*c);
  //Controller* getController();
  MainWindow* getMainwindow();
  ~MainWindow() = default;
private slots:



private:
  QDesktopWidget* desktop;

  QWidget* widget;

  QGridLayout* mainLayout;
  QVBoxLayout* v_layout;
  QVBoxLayout* buttonLayout;

  QLabel* title;
  QPushButton* adminBtn;
  QPushButton* clientBtn;

  Controller* controller;

  void setStyle();

};
#endif // MAINWINDOW_H

#ifndef CLIENT_H
#define CLIENT_H

#include <QLabel>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QFile>
#include "Mainwindow.h"

class Controller;

class Client : public QMainWindow
{
  Q_OBJECT
public:
  Client(QWidget *parent = nullptr);
  ~Client() = default;
  void setStyle();

private:
  QDesktopWidget* desktop;
  QGridLayout* mainLayout;
  QPushButton* nuovoUtente;
  QHBoxLayout* btnLayout;
  QWidget* widget;
  Controller* controller;


};

#endif // CLIENT_H

#ifndef CLIENT_H
#define CLIENT_H

#include <QLabel>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QFile>
#include <QLabel>

#include "mainwindow.h"

class Client : public QMainWindow
{
  Q_OBJECT
public:
  Client(Controller* c, QWidget *parent = nullptr);
  ~Client() = default;
  void setStyle();

private:
  QGridLayout* mainLayout;
  QPushButton* nuovoUtente;
  QPushButton* nuovaFamiglia;
  QVBoxLayout* btnLayout;
  QWidget* widget;
  QLabel* label;
  Controller* controller;


};

#endif // CLIENT_H

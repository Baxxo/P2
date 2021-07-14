#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "mainwindow.h"

class Client : public QMainWindow {
  Q_OBJECT
 public:
  Client(Controller* c, QWidget* parent = nullptr);
  ~Client() = default;
  void setStyle();

 private:
  QGridLayout* mainLayout;
  QPushButton* nuovoUtente;
  QPushButton* nuovaFamiglia;
  QPushButton* nuovoAbbonamento;
  QPushButton* nuovoBiglietto;
  QVBoxLayout* btnLayout;
  QWidget* widget;
  QLabel* label;
  Controller* controller;
};

#endif  // CLIENT_H

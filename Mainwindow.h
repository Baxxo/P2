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

#include "client.h"
#include "admin.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow() = default;
private slots:

  void openAdmin();
  void openClient();

private:
  QDesktopWidget* desktop;

  QWidget* widget;

  QGridLayout* mainLayout;
  QVBoxLayout* v_layout;
  QVBoxLayout* buttonLayout;

  QLabel* title;
  QPushButton* adminBtn;
  QPushButton* clientBtn;

  Admin* admin;
  Client* client;

  void setStyle();
};
#endif // MAINWINDOW_H

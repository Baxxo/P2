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


#include <iostream>
#include <QDebug>
#include <QDir>


using std::cout;
using std::endl;

class Admin : public QMainWindow
{
  Q_OBJECT
public:
  Admin(QWidget *parent = nullptr);
  ~Admin() = default;

private slots:
  //void read();
  //void write();


private:  
  QDesktopWidget* desktop;
  QGridLayout* baseLayout;
  QVBoxLayout* mainLayout;

  QLabel* label;
  QWidget* widget;

  QPushButton* readBtn;
  QPushButton* writeBtn;

  int i;

};

#endif // ADMIN_H

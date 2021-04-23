#ifndef ADMIN_H
#define ADMIN_H

#include <QLabel>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>


class Admin : public QMainWindow
{
  Q_OBJECT
public:
  Admin(QWidget *parent = nullptr);
  ~Admin() = default;

private:  
  QDesktopWidget* desktop;

  QLabel* label;
};

#endif // ADMIN_H

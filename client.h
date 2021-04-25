#ifndef CLIENT_H
#define CLIENT_H

#include <QLabel>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>

class Client : public QMainWindow
{
  Q_OBJECT
public:
  Client(QWidget *parent = nullptr);
  ~Client() = default;

private:
  QDesktopWidget* desktop;
  QGridLayout* baseLayout;
  QHBoxLayout* mainLayout;

  QLabel* label;

};

#endif // CLIENT_H

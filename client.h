#ifndef CLIENT_H
#define CLIENT_H

#include <QLabel>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>

class Client : public QMainWindow
{
  Q_OBJECT
public:
  Client(QWidget *parent = nullptr);
  ~Client() = default;

private:
  QDesktopWidget* desktop;

  QLabel* label;

};

#endif // CLIENT_H

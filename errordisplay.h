#ifndef ERRORDISPLAY_H
#define ERRORDISPLAY_H

#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

class ErrorDisplay : public QWidget {
 public:
  ErrorDisplay(QWidget *parent = Q_NULLPTR, QString errorMessage = "");

  void setMessage(const QString &message);

 private:
  QLabel *mess;
  QVBoxLayout *layout;

  QDesktopWidget *desktop;
};

#endif  // ERRORDISPLAY_H

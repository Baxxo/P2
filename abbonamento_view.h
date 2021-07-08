#ifndef ABBONAMENTO_VIEW_H
#define ABBONAMENTO_VIEW_H

#include <QWidget>
#include "mainwindow.h"

class Abbonamento_view : public QWidget {
  Q_OBJECT
 private:
  Controller* controller;

 private slots:

  void resizeMe();

 public:
  explicit Abbonamento_view(Controller* c, QWidget* parent = nullptr);
};

#endif  // ABBONAMENTO_VIEW_H

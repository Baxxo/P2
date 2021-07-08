#ifndef ABBONAMENTO_VIEW_H
#define ABBONAMENTO_VIEW_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QWidget>

#include "mainwindow.h"

class Abbonamento_view : public QWidget {
  Q_OBJECT
 private:
  Controller* controller;
  QGroupBox* tipoAbbonamento;
  QHBoxLayout* layoutRadio;
  QRadioButton* abbonamento;
  QRadioButton* abbonamentoFamigliare;

 private slots:

  void resizeMe();

 public:
  explicit Abbonamento_view(Controller* c, QWidget* parent = nullptr);
};

#endif  // ABBONAMENTO_VIEW_H

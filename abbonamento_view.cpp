#include "abbonamento_view.h"

Abbonamento_view::Abbonamento_view(Controller *c, QWidget *parent)
    : QWidget(parent),
      controller(c),
      tipoAbbonamento(new QGroupBox),
      layoutRadio(new QHBoxLayout),
      abbonamento(new QRadioButton("Abbonamento")),
      abbonamentoFamigliare(new QRadioButton("Abbonamento Famigliare")) {
  abbonamento->setChecked(true);
  layoutRadio->addWidget(abbonamento);
  layoutRadio->addWidget(abbonamentoFamigliare);
  tipoAbbonamento->setLayout(layoutRadio);
}

void Abbonamento_view::resizeMe() { adjustSize(); }

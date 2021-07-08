#include "abbonamento_view.h"

Abbonamento_view::Abbonamento_view(Controller *c, QWidget *parent)
    : QWidget(parent), controller(c) {}

void Abbonamento_view::resizeMe() { adjustSize(); }

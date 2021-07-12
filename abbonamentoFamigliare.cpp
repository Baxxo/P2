#include "abbonamentoFamigliare.h"
#include <QDebug>

AbbonamentoFamigliare::AbbonamentoFamigliare(Data *d, string u, string f,
                                             double p, string c, int e)
    : Abbonamento(d, u, p, c, e), famiglia(f) {}

AbbonamentoFamigliare::AbbonamentoFamigliare(const AbbonamentoFamigliare &o)
    : Abbonamento(o), famiglia(o.famiglia) {}

// AbbonamentoFamigliare::~AbbonamentoFamigliare() {}

std::string AbbonamentoFamigliare::getFamiglia() const { return famiglia; }

AbbonamentoFamigliare *AbbonamentoFamigliare::clone() const {
  // qDebug() << "clone AbbonamentoFamigliare";
  return new AbbonamentoFamigliare(*this);
}

double AbbonamentoFamigliare::getPrezzo() const {
  return EntrataFilm::getPrezzo() * getEntrate();
}

AbbonamentoFamigliare &AbbonamentoFamigliare::operator=(
    const AbbonamentoFamigliare &o) {
  if (this != &o) {
    Abbonamento::operator=(o);
    famiglia = o.famiglia;
  }
  return *this;
}

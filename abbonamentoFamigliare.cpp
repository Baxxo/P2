#include "abbonamentoFamigliare.h"

AbbonamentoFamigliare::AbbonamentoFamigliare(Data *d, string u, string f,
                                             double p, string c, int e,
                                             unsigned int mF)
    : Abbonamento(d, u, p, c, e), famiglia(f), membriFamiglia(mF) {}

AbbonamentoFamigliare::AbbonamentoFamigliare(const AbbonamentoFamigliare &o)
    : Abbonamento(o), famiglia(o.famiglia) {}

string AbbonamentoFamigliare::getFamiglia() const { return famiglia; }

AbbonamentoFamigliare *AbbonamentoFamigliare::clone() const {
  return new AbbonamentoFamigliare(*this);
}

std::string AbbonamentoFamigliare::toString() const {
  return "Codice: " + getCodice() + " famiglia: " + getFamiglia();
}

unsigned int AbbonamentoFamigliare::getNumeroMembri() const {
  return membriFamiglia;
}

double AbbonamentoFamigliare::getPrezzo() const {
  return Abbonamento::getPrezzo() * getEntrate() * membriFamiglia;
}

AbbonamentoFamigliare &AbbonamentoFamigliare::operator=(
    const AbbonamentoFamigliare &o) {
  if (this != &o) {
    Abbonamento::operator=(o);
    famiglia = o.famiglia;
  }
  return *this;
}

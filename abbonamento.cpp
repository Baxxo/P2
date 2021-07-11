#include "abbonamento.h"
#include <QDebug>

Abbonamento::Abbonamento(Data *d, Utente *u, double p, string cod, int entr)
    : EntrataFilm(d, u, p), codice(cod), entrate(entr) {}

Abbonamento::Abbonamento(const Abbonamento &o)
    : EntrataFilm(o), codice(o.codice), entrate(o.entrate) {}

int Abbonamento::getEntrate() const { return entrate; }

double Abbonamento::getPrezzo() const {
  return EntrataFilm::getPrezzo() * getEntrate();
}

std::string Abbonamento::getCodice() const { return codice; }

Abbonamento &Abbonamento::operator=(const Abbonamento &o) {
  if (this != &o) {
    codice = o.codice;
    entrate = o.entrate;
  }
  return *this;
}

bool Abbonamento::operator==(const Abbonamento &o) const {
  return o.getCodice() == codice;
}

Abbonamento *Abbonamento::clone() const {
  qDebug() << "clone Abb";
  return new Abbonamento(*this);
}

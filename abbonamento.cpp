#include "abbonamento.h"

Abbonamento::Abbonamento(Data *d, string u, double p, string cod, int entr)
    : EntrataFilm(cod, d, u, p), entrate(entr) {}

Abbonamento::Abbonamento(const Abbonamento &o)
    : EntrataFilm(o), entrate(o.entrate) {}

int Abbonamento::getEntrate() const { return entrate; }

int Abbonamento::removeOneEntrata() { --entrate; }

double Abbonamento::getPrezzo() const {
  return EntrataFilm::getPrezzo() * getEntrate();
}
Abbonamento &Abbonamento::operator=(const Abbonamento &o) {
  if (this != &o) {
    EntrataFilm::operator=(o);
    entrate = o.entrate;
  }
  return *this;
}

Abbonamento *Abbonamento::clone() const { return new Abbonamento(*this); }

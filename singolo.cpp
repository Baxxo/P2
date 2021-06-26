#include "singolo.h"

Singolo::Singolo(Data *d, Utente *u, double p, string c, int e, int f)
    : Abbonamento(d, u, p, c, e), fascia_oraria(f) {}

double Singolo::getFasciaOraria() const {

  switch (fascia_oraria) {
  case 1:
    return 0.5;
  case 2:
    return 0.7;
  case 3:
    return 0.8;
  case 4:
    return 0.9;
  default:
    return 1;
  }
}

double Singolo::getPrezzo() const {

  return EntrataFilm::getPrezzo() * getFasciaOraria() * getEntrate();
}

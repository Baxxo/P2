#include "biglietto.h"

Biglietto::Biglietto(Data *d, Utente *u, double p, bool r, string f)
    : EntrataFilm(d, u, p), riduzione(r), film(f) {}

Biglietto::Biglietto(const Biglietto &o)
    : EntrataFilm(o), riduzione(o.riduzione), film(o.film) {}

bool Biglietto::getRiduzione() const { return riduzione; }

string Biglietto::getFilm() const { return film; }

double Biglietto::getPrezzo() const {
  return EntrataFilm::getPrezzo() - (getRiduzione() * 0.85);
}

Biglietto *Biglietto::clone() const { return new Biglietto(*this); }

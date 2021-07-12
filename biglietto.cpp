#include "biglietto.h"
#include <QDebug>

Biglietto::Biglietto(std::string c, Data *d, std::string u, double p, bool r,
                     string f)
    : EntrataFilm(c, d, u, p), riduzione(r), film(f) {}

Biglietto::Biglietto(const Biglietto &o)
    : EntrataFilm(o), riduzione(o.riduzione), film(o.film) {}

bool Biglietto::getRiduzione() const { return riduzione; }

Biglietto &Biglietto::operator=(const Biglietto &o) {
  if (this != &o) {
    EntrataFilm::operator=(o);
    riduzione = o.riduzione;
    film = o.film;
  }

  return *this;
}

string Biglietto::getFilm() const { return film; }

double Biglietto::getPrezzo() const {
  return EntrataFilm::getPrezzo() - (getRiduzione() * 0.85);
}

Biglietto *Biglietto::clone() const {
  // qDebug() << "clone entrata";
  return new Biglietto(*this);
}

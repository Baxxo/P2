#include "entrataFilm.h"

EntrataFilm::EntrataFilm(Data *d, Utente *u, double p)
    : utente(u), data(d), prezzo(p) {}

double EntrataFilm::getPrezzo() const { return prezzo; }

Data *EntrataFilm::getData() const { return data; }

Utente *EntrataFilm::getUtente() const { return utente; }

bool EntrataFilm::operator==(const EntrataFilm &o) const {
  return o.getData() == data && o.getPrezzo() == prezzo &&
         o.getUtente() == utente;
}

EntrataFilm *EntrataFilm::clone() const { return new EntrataFilm(*this); }

std::string EntrataFilm::toString() const {
  return utente->getCodFisc() + " " + data->ToString();
}

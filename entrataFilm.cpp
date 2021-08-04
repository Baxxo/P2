#include "entrataFilm.h"
#include <QDebug>

EntrataFilm::EntrataFilm(string cod, Data *d, string u, double p)
    : codice(cod), utente(u), data(d), prezzo(p) {}

EntrataFilm::EntrataFilm(const EntrataFilm &o)
    : codice(o.codice), utente(o.utente), data(o.data), prezzo(o.prezzo) {}

double EntrataFilm::getPrezzo() const { return prezzo; }

Data *EntrataFilm::getData() const { return data; }

string EntrataFilm::getUtente() const { return utente; }

bool EntrataFilm::operator==(const EntrataFilm &o) const {
  return o.codice == codice;
}

bool EntrataFilm::operator!=(const EntrataFilm &o) const {
  return o.codice != codice;
}

EntrataFilm &EntrataFilm::operator=(const EntrataFilm &o) {
  if (this != &o) {
    codice = o.codice;
    utente = o.utente;
    data = o.data;
    prezzo = o.prezzo;
  }
  return *this;
}

EntrataFilm *EntrataFilm::clone() const { return new EntrataFilm(*this); }

string EntrataFilm::toString() const {
  return "Utente: " + utente + " - Data: " + data->ToString();
}

string EntrataFilm::getCodice() const { return codice; }

#include "EntrataFilm.h"

EntrataFilm::EntrataFilm(Data* d, Utente* u, double p)
    : utente(u),data(d), prezzo(p)
    {}

EntrataFilm::~EntrataFilm(){
    delete data;
    delete utente;
}
double EntrataFilm::getPrezzo() const{
    return prezzo;
}

string EntrataFilm::getData() const{
  return data->ToString();
}

Utente *EntrataFilm::getUtente() const
{
  return utente;
}

#include "EntrataFilm.h"

EntrataFilm::EntrataFilm(Data* d, Utente* u, double p)
    : utente(u),data(d), prezzo(p)
    {}

EntrataFilm::~EntrataFilm(){
    delete data;
    delete utente;
}
double EntrataFilm::GetPrezzo() const{
    return prezzo;
}

string EntrataFilm::GetData() const{
    return data->ToString();
}

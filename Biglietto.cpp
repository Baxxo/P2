#include "Biglietto.h"

Biglietto::Biglietto(Data* d, Utente* u, double p, bool r, string f)
        :EntrataFilm(d, u, p), riduzione(r), film(f)
        {}

bool Biglietto::getRiduzione() const{
    return riduzione;
}

string Biglietto::getFilm() const{
    return film;
}

double Biglietto::getPrezzo() const{

    if(getRiduzione()){
        return EntrataFilm::getPrezzo()*0.85;
    }

    else return EntrataFilm::getPrezzo();
}

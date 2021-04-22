#include "Biglietto.h"

Biglietto::Biglietto(Data* d, Utente* u, double p, bool r, string f)
        :EntrataFilm(d, u, p), riduzione(r), film(f)
        {}

bool Biglietto::GetRiduzione() const{
    return riduzione;
}

string Biglietto::GetFilm() const{
    return film;
}

double Biglietto::GetPrezzo() const{

    if(GetRiduzione()){
        return EntrataFilm::GetPrezzo()*0.85;
    }

    else return EntrataFilm::GetPrezzo();
}

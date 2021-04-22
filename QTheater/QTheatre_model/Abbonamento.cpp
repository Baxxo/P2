#include "Abbonamento.h"

Abbonamento::Abbonamento(Data* d, Utente* u, double p, string c, int e)
    : EntrataFilm(d, u, p), codice(c), entrate(e)
    {}

int Abbonamento::GetEntrate() const{
    return entrate;
}

double Abbonamento::GetPrezzo() const{
    return EntrataFilm::GetPrezzo()*GetEntrate();
}

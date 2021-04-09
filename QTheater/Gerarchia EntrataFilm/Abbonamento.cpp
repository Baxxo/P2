#include "Abbonamento.h"

Abbonamento::Abbonamento(double p, Data d, string c, int e)
	: EntrataFilm(d, p), codice{c}, entrate{e}
	{}

int Abbonamento::GetEntrate() const{
	return entrate;
}
	
double Abbonamento::GetPrezzo() const{
	return EntrataFilm::GetPrezzo()*Abbonamento::GetEntrate();
}

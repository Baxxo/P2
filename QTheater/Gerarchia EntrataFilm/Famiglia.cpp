#include "Famiglia.h"

Famiglia::Famiglia(double p, Data d, string c, int e, int n)
	:Abbonamento(p, d, c, e), numero_membri{n}
	{}
	
int Famiglia::GetNumeroMembri() const{
	return numero_membri;
}

double Famiglia::GetPrezzo() const{
	
	return EntrataFilm::GetPrezzo()*Abbonamento::GetEntrate()*Famiglia::GetNumeroMembri();
	
}


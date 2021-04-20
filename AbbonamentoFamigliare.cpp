#include "AbbonamentoFamigliare.h"

AbbonamentoFamigliare::AbbonamentoFamigliare(Data* d, Utente* u, double p, string c, int e, int n)
	:Abbonamento(d, u, p, c, e), numero_membri(n)
	{}
	
int AbbonamentoFamigliare::GetNumeroMembri() const{
	return numero_membri;
}

double AbbonamentoFamigliare::GetPrezzo() const{
	
	return EntrataFilm::GetPrezzo()*GetEntrate()*GetNumeroMembri();
	
}


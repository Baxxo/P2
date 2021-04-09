#include "Biglietto.h"

Biglietto::Biglietto(double p, bool r, string f, Data d)
		:EntrataFilm(d, p), riduzione{r}, film{f}
		{}

bool Biglietto::GetRiduzione() const{
	return riduzione;
}

string Biglietto::GetFilm() const{
	return film;
}

double Biglietto::GetPrezzo() const{
	
	if(Biglietto::GetRiduzione()==true){
		return prezzo*0.85;
	}
	
	else return prezzo;
}

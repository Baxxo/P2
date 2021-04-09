#include "Singolo.h"

Singolo::Singolo(double p, Data d, string c, int e, int f)
	: Abbonamento(p, d, c, e), fascia_oraria{f}
	{}
	
double Singolo::GetFasciaOraria() const{
	if(fascia_oraria==1){
		return 0.5;
	}
	if(fascia_oraria==2){
		return 0.7;
	}
	if(fascia_oraria==3){
		return 0.8;
	}
	if(fascia_oraria==4){
		return 0.9;
	}
}
	
double Singolo::GetPrezzo() const{
	
	return EntrataFilm::GetPrezzo()*Singolo::GetFasciaOraria()*Abbonamento::GetEntrate();
	
}

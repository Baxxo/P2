#include "Singolo.h"

Singolo::Singolo(double p, Data d, string c, int e, int f)
	: Abbonamento(p, d, c, e), fascia_oraria{f}
	{}
	
double Singolo::GetFasciaOraria() const{
	unsigned int i = 1;
	if(fascia_oraria==1){
		i=  0.5;
	} else if(fascia_oraria==2){
		i=  0.7;
	} else if(fascia_oraria==3){
		i=  0.8;
	} else if(fascia_oraria==4){
		i=  0.9;
	}
	return i;
}
	
double Singolo::GetPrezzo() const{
	
	return EntrataFilm::GetPrezzo()*Singolo::GetFasciaOraria()*Abbonamento::GetEntrate();
	
}

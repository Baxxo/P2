#include <iostream>
#include "EntrataFilm.h"

EntrataFilm::EntrataFilm(double p){
	
	prezzo=p;
	
}

double EntrataFilm::GetPrezzo() const{
	return prezzo;
}

Data EntrataFilm::GetData() const{
	return data;
}

std::ostream& operator<<(ostream &os, const EntrataFilm &e){
	return os << e.GetPrezzo();
}




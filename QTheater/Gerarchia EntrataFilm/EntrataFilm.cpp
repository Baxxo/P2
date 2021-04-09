#include "EntrataFilm.h"


EntrataFilm::EntrataFilm(Data d, double p)
	: data {d}, prezzo{p}
	{}

double EntrataFilm::GetPrezzo() const{
	return prezzo;
}

Data EntrataFilm::GetData() const{
	return data;
}

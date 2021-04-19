#include "EntrataFilm.h"



EntrataFilm::EntrataFilm(Data* d, Utente* u, double p)
	: data(d), utente(u), prezzo(p)
	{}
	
EntrataFilm::~EntrataFilm(){
	delete data;
	delete utente;
}
double EntrataFilm::GetPrezzo() const{
	return prezzo;
}

string EntrataFilm::GetData() const{
	return data->ToString();
}

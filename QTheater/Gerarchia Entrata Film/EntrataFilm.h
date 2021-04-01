#include <iostream>
#include "Data.h"

using std::cout;
using std::ostream;

class EntrataFilm{
	
	private:
	
	//Utente utente;
	
	Data data;
	
	float prezzo;
		
	
	public:
	
	EntrataFilm(/*Utente*/ float=7.5);
	
	float GetPrezzo() const;
	
	Data GetData() const;
		
	friend ostream& operator<<(ostream, const EntrataFilm);

};

	

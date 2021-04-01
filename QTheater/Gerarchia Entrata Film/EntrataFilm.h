#include <iostream>
#include "Data.h"

using std::cout;
using std::ostream;

class EntrataFilm{
	
	private:
	
	//Utente utente;
	
	Data data;
	
	double prezzo;
		
	
	public:
	
	EntrataFilm(/*Utente*/ double=7.5);
	
	double GetPrezzo() const;
	
	Data GetData() const;
		
	friend ostream& operator<<(ostream, const EntrataFilm);

};

	

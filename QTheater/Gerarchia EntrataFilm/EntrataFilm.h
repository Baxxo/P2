#include "Data.h"
#ifndef ENTRATAFILM
#define ENTRATAFILM 1

class EntrataFilm{
	
	protected:
	
	//Utente utente;
	
	Data data;
	
	double prezzo;
		
	
	
	public:
	
	EntrataFilm(Data=Data(0,0,0), double=7.5);
	
	virtual double GetPrezzo() const;
	
	Data GetData() const;
		
};
#endif

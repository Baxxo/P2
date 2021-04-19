#include "Data.h"
#include "Utente.h"
#ifndef ENTRATAFILM
#define ENTRATAFILM 1

class EntrataFilm{
	
	private:
	
	Utente* utente= new Utente;
	
	Data* data= new  Data;
	
	double prezzo;
		
	
	
	public:
		
	~EntrataFilm();
	
	EntrataFilm(Data*, Utente*, double=7.5);
	
	virtual double GetPrezzo() const;
	
	string GetData() const;
		
};
#endif

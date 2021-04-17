#include "EntrataFilm.h"
#ifndef BIGLIETTO
#define BIGLIETTO 1

class Biglietto: public EntrataFilm{
	
	private:
		bool riduzione;
		string film;
		
		
	public:
		
		Biglietto(Data*, Utente*, double=7.5, bool=false, string="null");
		
		bool GetRiduzione() const;
		string GetFilm() const;
		double GetPrezzo() const override;
		
};

#endif


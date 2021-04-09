#include "EntrataFilm.h"
#ifndef BIGLIETTO
#define BIGLIETTO 1

class Biglietto: public EntrataFilm{
	
	private:
		bool riduzione;
		string film;
		Data data_ora_acquisto; //ridefinizione di data di EntrafaFilm(?)
		//posto
		
		
	public:
		
		Biglietto(double=7.5, bool=false, string="null", Data=Data(0,0,0));
		
		bool GetRiduzione() const;
		string GetFilm() const;
		double GetPrezzo() const override;
		
};

#endif


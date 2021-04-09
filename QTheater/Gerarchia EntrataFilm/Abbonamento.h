#include "EntrataFilm.h"
#ifndef ABBONAMENTO
#define ABBONAMENTO 1

class Abbonamento: public EntrataFilm{
	
	protected:
		string codice;
		int entrate;
		
	
	public:
		
		Abbonamento(double=7.5, Data=Data(0,0,0), string="00000", int=0);
		
		int GetEntrate() const;
		
		double GetPrezzo() const override;		
		

		
	
};
#endif

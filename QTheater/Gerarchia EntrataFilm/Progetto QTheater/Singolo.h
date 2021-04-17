#include "Abbonamento.h"
#ifndef SINGOLO
#define SINGOLO 1

class Singolo: public Abbonamento{
	
	private:
		int fascia_oraria;
		
	public:
		
		Singolo(Data*, Utente*, double=7.5, string="00000", int=0, int=0);
		
		double GetFasciaOraria() const;
		
		double GetPrezzo() const override;
		
};

#endif

#include "Abbonamento.h"
#ifndef SINGOLO
#define SINGOLO 1

class Singolo: public Abbonamento{
	
	private:
		int fascia_oraria;
		
	public:
		
		Singolo(double p, Data d, string c, int e, int f);
		
		double GetFasciaOraria() const;
		
		double GetPrezzo() const override;
		
};

#endif

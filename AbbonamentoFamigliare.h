#include "Abbonamento.h"
#ifndef ABBONAMENTOFAMIGLIARE
#define ABBONAMENTOFAMIGLIARE 1

class AbbonamentoFamigliare:public Abbonamento{
	
	private:
		int numero_membri;
		
	public:
		
		AbbonamentoFamigliare(Data*, Utente*, double=7.5, string="00000", int=0, int=0);
		
		int GetNumeroMembri() const;
		
		double GetPrezzo() const override;		
		
	
};

#endif

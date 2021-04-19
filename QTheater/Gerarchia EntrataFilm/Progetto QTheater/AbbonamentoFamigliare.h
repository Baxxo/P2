#include "Abbonamento.h"
#include "Famiglia.h"
#ifndef ABBONAMENTOFAMIGLIARE
#define ABBONAMENTOFAMIGLIARE 1

class AbbonamentoFamigliare:public Abbonamento{
	
	private:
		Famiglia* famiglia= new Famiglia;
		
	public:
		
		~AbbonamentoFamigliare();
		
		AbbonamentoFamigliare(Data*, Utente*, Famiglia*, double=7.5, string="00000", int=0);
		
		double GetPrezzo() const override;		
		
	
};

#endif

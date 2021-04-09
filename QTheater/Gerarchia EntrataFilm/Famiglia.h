#include "Abbonamento.h"
#ifndef FAMIGLIA
#define FAMIGLIA 1

class Famiglia:public Abbonamento{
	
	private:
		int numero_membri;
		
	public:
		
		Famiglia(double=7.5, Data=Data(0,0,0), string="00000", int=0, int=0);
		
		int GetNumeroMembri() const;
		
		double GetPrezzo() const override;		
		
	
};

#endif

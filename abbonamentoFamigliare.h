#include "abbonamento.h"
#include "famiglia.h"
#ifndef ABBONAMENTOFAMIGLIARE
#define ABBONAMENTOFAMIGLIARE 1

class AbbonamentoFamigliare: public Abbonamento{

private:
  Famiglia* famiglia= new Famiglia();

public:

  ~AbbonamentoFamigliare();

  AbbonamentoFamigliare(Data* d, Utente* u, Famiglia* f, double p=7.5, string c ="00000", int e=0);

  double getPrezzo() const;


};

#endif

#ifndef ABBONAMENTOFAMIGLIARE
#define ABBONAMENTOFAMIGLIARE
#include "abbonamento.h"
#include "famiglia.h"

class AbbonamentoFamigliare : public Abbonamento {

private:
  Famiglia *famiglia;

public:
  AbbonamentoFamigliare(Data *d, Utente *u, Famiglia *f, double p = 7.5,
                        string c = "00000", int e = 0);

  double getPrezzo() const;

  virtual ~AbbonamentoFamigliare();
};

#endif

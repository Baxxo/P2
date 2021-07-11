#ifndef ABBONAMENTOFAMIGLIARE
#define ABBONAMENTOFAMIGLIARE
#include "abbonamento.h"
#include "famiglia.h"

class AbbonamentoFamigliare : public Abbonamento {
 private:
  Famiglia *famiglia;

 public:
  AbbonamentoFamigliare(Data *d = nullptr, Utente *u = nullptr,
                        Famiglia *f = nullptr, double p = 7.5,
                        string c = "00000", int e = 0);

  AbbonamentoFamigliare(const AbbonamentoFamigliare &o);

  double getPrezzo() const;

  ~AbbonamentoFamigliare();

  Famiglia *getFamiglia() const;

  AbbonamentoFamigliare *clone() const;
};

#endif

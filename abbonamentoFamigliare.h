#ifndef ABBONAMENTOFAMIGLIARE
#define ABBONAMENTOFAMIGLIARE
#include "abbonamento.h"
#include "famiglia.h"

using std::string;

class AbbonamentoFamigliare : public Abbonamento {
 private:
  string famiglia;
  unsigned int membriFamiglia;

 public:
  AbbonamentoFamigliare(Data *d = nullptr, string u = "", string f = "",
                        double p = 7.5, string c = "00000", int e = 0,
                        unsigned int mF = 0);

  AbbonamentoFamigliare(const AbbonamentoFamigliare &o);

  ~AbbonamentoFamigliare() = default;

  double getPrezzo() const;

  AbbonamentoFamigliare &operator=(const AbbonamentoFamigliare &o);

  AbbonamentoFamigliare *clone() const override;

  string toString() const override;

  unsigned int getNumeroMembri() const;

  string getFamiglia() const;
};

#endif

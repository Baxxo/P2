#ifndef ABBONAMENTOFAMIGLIARE
#define ABBONAMENTOFAMIGLIARE
#include "abbonamento.h"
#include "famiglia.h"

using std::string;

class AbbonamentoFamigliare : public Abbonamento {
 private:
  string famiglia;

 public:
  AbbonamentoFamigliare(Data *d = nullptr, string u = "", string f = "",
                        double p = 7.5, string c = "00000", int e = 0);

  AbbonamentoFamigliare(const AbbonamentoFamigliare &o);

  double getPrezzo() const;

  AbbonamentoFamigliare &operator=(const AbbonamentoFamigliare &o);

  ~AbbonamentoFamigliare() = default;

  string getFamiglia() const;

  AbbonamentoFamigliare *clone() const override;

  string toString() const override;
};

#endif

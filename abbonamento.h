#ifndef ABBONAMENTO
#define ABBONAMENTO
#include "entrataFilm.h"
using std::string;

class Abbonamento : public EntrataFilm {
 private:
  string codice;
  int entrate;

 public:
  Abbonamento(Data *d = new Data(), Utente *u = new Utente(), double p = 7.5,
              string cod = "00000", int entr = 0);

  Abbonamento(const Abbonamento &o);

  ~Abbonamento() = default;

  int getEntrate() const;

  double getPrezzo() const;

  string getCodice() const;

  Abbonamento &operator=(const Abbonamento &o);

  bool operator==(const Abbonamento &o) const;

  Abbonamento *clone() const;
};
#endif

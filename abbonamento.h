#ifndef ABBONAMENTO
#define ABBONAMENTO
#include "entrataFilm.h"

//#include <iostream>

// using std::cout;

class Abbonamento : public EntrataFilm {
 private:
  std::string codice;
  int entrate;

 public:
  Abbonamento(Data *d = new Data(), Utente *u = new Utente(), double p = 7.5,
              string cod = "00000", int entr = 0);

  ~Abbonamento() = default;

  int getEntrate() const;

  double getPrezzo() const;

  std::string getCodice() const;

  Abbonamento &operator=(const Abbonamento &o);

  bool operator==(const Abbonamento &o) const;
};
#endif

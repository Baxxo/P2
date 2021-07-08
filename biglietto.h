#ifndef BIGLIETTO
#define BIGLIETTO
#include "entrataFilm.h"

class Biglietto : public EntrataFilm {
 private:
  bool riduzione;
  string film;

 public:
  Biglietto(Data *d, Utente *u, double p = 7.5, bool r = false,
            string f = "null");

  ~Biglietto() = default;

  bool getRiduzione() const;
  string getFilm() const;
  double getPrezzo() const override;
};

#endif

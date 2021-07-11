#ifndef BIGLIETTO
#define BIGLIETTO
#include "entrataFilm.h"

using std::string;

class Biglietto : public EntrataFilm {
 private:
  bool riduzione;
  string film;

 public:
  Biglietto(Data *d, Utente *u, double p = 7.5, bool r = false,
            string f = "null");
  Biglietto(const Biglietto &o);

  ~Biglietto() = default;

  bool getRiduzione() const;

  string getFilm() const;

  double getPrezzo() const;

  Biglietto *clone() const;
};

#endif

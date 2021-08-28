#ifndef BIGLIETTO
#define BIGLIETTO
#include "entrataFilm.h"
using std::string;

class Biglietto : public EntrataFilm {
 private:
  bool riduzione;
  string film;

 public:
  Biglietto(string c = "0", Data *d = new Data(), string u = "", double p = 7.5,
            bool r = false, string f = "null");
  Biglietto(const Biglietto &o);

  ~Biglietto() = default;

  bool getRiduzione() const;

  Biglietto &operator=(const Biglietto &o);

  string getFilm() const;

  double getPrezzo() const;

  Biglietto *clone() const override;
};

#endif

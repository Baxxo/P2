#ifndef ENTRATAFILM
#define ENTRATAFILM
#include "data.h"
#include "utente.h"

class EntrataFilm {

private:
  Utente *utente;

  Data *data;

  double prezzo;

public:
  virtual ~EntrataFilm() = default;

  EntrataFilm(Data *d = nullptr, Utente *u = nullptr, double p = 7.5);

  virtual double getPrezzo() const;

  Data *getData() const;

  virtual Utente *getUtente() const;

  virtual bool operator==(const EntrataFilm &o) const;

  virtual EntrataFilm *clone() const;

  string toString() const;
};
#endif

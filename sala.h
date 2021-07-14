#ifndef SALA
#define SALA

#include "utente.h"
using std::string;

class Sala {
 private:
  int righe;
  int colonne;
  string nome_sala;

 public:
  Sala(int r = 0, int c = 0, string n = "null");
  Sala(const Sala &o);
  int getRighe() const;
  int getColonne() const;
  string getNomesala() const;
  virtual Sala *clone() const;

  bool operator==(const Sala &o) const;
  bool operator!=(const Sala &o) const;
};

#endif

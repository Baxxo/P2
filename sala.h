#ifndef SALA
#define SALA

#include "utente.h"
using std::string;

class Sala {
 private:
  unsigned int righe;
  unsigned int colonne;
  string nome_sala;

 public:
  Sala(unsigned int r = 0, unsigned int c = 0, string n = "null");
  Sala(const Sala &o);

  virtual ~Sala() = default;

  unsigned int getRighe() const;
  unsigned int getColonne() const;
  string getNomesala() const;
  virtual Sala *clone() const;

  bool operator==(const Sala &o) const;
  bool operator!=(const Sala &o) const;
};

#endif

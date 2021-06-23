#ifndef SALA
#define SALA

#include "utente.h"
using std::string;

class Sala {

private:
  int righe;
  int colonne;
  string nome_sala;
  Utente *matrix;

public:
  ~Sala();
  Sala(int r = 0, int c = 0, string n = "null");
  int getRighe() const;
  int getColonne() const;
  string getNomesala() const;
  virtual Sala *clone() const;
};

#endif

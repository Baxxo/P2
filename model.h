#ifndef MODEL_H
#define MODEL_H

//#include "abbonamento.h"
#include "abbonamentoFamigliare.h"
#include "myVector.h"

class Model
{
public:
  Model();
  void addEntrata(const EntrataFilm *a);

  void removeEntrata(EntrataFilm *a);

private:
  Famiglia* f;
  MyVector<EntrataFilm> listAbbonamento;
};

#endif // MODEL_H

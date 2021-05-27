#ifndef MODEL_H
#define MODEL_H

#include "abbonamentoFamigliare.h"
#include "myVector.h"

class Model
{
public:
  Model();
  void addEntrata(const EntrataFilm *a);

  bool removeEntrata(EntrataFilm *a);

private:
  Famiglia* f;
  MyVector<EntrataFilm> listAbbonamento;
};

#endif // MODEL_H

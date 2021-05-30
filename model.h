#ifndef MODEL_H
#define MODEL_H

#include "abbonamentoFamigliare.h"
#include "myVector.h"

class Model
{
public:
  Model();
  void addEntrata(const EntrataFilm *a);
  void addUtente(const Utente *u);
  void addFamiglia(const Famiglia *f);

  bool removeEntrata(const EntrataFilm *a);
  bool removeUtente(const Utente *u);
  bool removeFamiglia(const Famiglia *f);

  Utente *getUtente(string cf);
  Famiglia *getFamiglia(string cf);
  EntrataFilm *getEntrataFilm();

private:
  MyVector<EntrataFilm> listEntrate;
  MyVector<Utente> listUtenti;
  MyVector<Famiglia> listFamiglie;
};

#endif // MODEL_H

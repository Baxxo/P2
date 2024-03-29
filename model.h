#ifndef MODEL_H
#define MODEL_H

#include "abbonamentoFamigliare.h"
#include "biglietto.h"
#include "deepPtr.h"
#include "myVector.h"
#include "sala.h"

using std::string;

class Model {
 public:
  Model();

  void addEntrata(EntrataFilm *e);
  void addUtente(Utente *u);
  void addFamiglia(Famiglia *f);
  void addSala(Sala *s);

  ~Model() = default;

  bool removeEntrata(const std::string &e);
  bool removeUtente(const Utente &u);
  bool removeFamiglia(const Famiglia &f);
  bool removeSala(const Sala &s);

  void clearVectorUtenti();
  void clearVectorFamiglie();
  void clearVectorEntrate();
  void cleaVectorSale();

  Utente *getUtente(string cf) const;
  Famiglia *getFamiglia(string name) const;
  EntrataFilm *getEntrataFilm(string cod) const;
  Sala *getSala(string nome) const;

  unsigned int sizeUtenti() const;
  Utente *getUser(unsigned int pos) const;

  unsigned int sizeFamilies() const;
  Famiglia *getFamily(unsigned int pos) const;

  unsigned int sizeEntrate() const;
  EntrataFilm *getEntrata(unsigned int pos) const;

  unsigned int sizeSale() const;
  Sala *getSala_byPos(unsigned int pos) const;

  void addUserToFamily(Famiglia &f, Utente *u);

  bool searchCf(const string &cf) const;
  bool searchNameFamiglia(const string &name) const;
  bool searchEntrata(const string &cod) const;
  bool seachEntrataByUtente(const string &utente) const;

  string getTest() const;

 private:
  MyVector<DeepPtr<EntrataFilm>> listEntrate;
  MyVector<DeepPtr<Utente>> listUtenti;
  MyVector<DeepPtr<Famiglia>> listFamiglie;
  MyVector<DeepPtr<Sala>> listSale;
};

#endif  // MODEL_H

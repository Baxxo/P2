#ifndef MODEL_H
#define MODEL_H

#include "abbonamentoFamigliare.h"
#include "deepPtr.h"
#include "myVector.h"
#include "sala.h"

class Model {
 public:
  Model(string _test = "test");
  void addEntrata(EntrataFilm *e);
  void addUtente(const Utente &u);
  void addFamiglia(const Famiglia &f);
  void addAcquisto(const Utente &u);
  void addSala(const Sala &s);

  ~Model() = default;

  bool removeEntrata(const EntrataFilm &a);
  bool removeUtente(const Utente &u);
  bool removeFamiglia(const Famiglia &f);
  bool removeAcquisto(const Utente &u);
  bool removeSala(const Sala &s);

  void clearVectorUtenti();
  void clearVectorFamiglie();
  void cleaVectorSale();

  Utente *getUtente(string cf);
  Famiglia *getFamiglia(string name);
  EntrataFilm *getEntrataFilm();
  Sala *getSala(string nome);

  const MyVector<DeepPtr<EntrataFilm>> &getListEntrate() const;
  const MyVector<DeepPtr<Utente>> &getListUtenti() const;
  const MyVector<DeepPtr<Famiglia>> &getListFamiglie() const;
  const MyVector<DeepPtr<Sala>> &getListSale() const;

  void addUserToFamily(Famiglia &f, Utente *u);

  bool searchCf(const string &cf) const;
  bool searchNameFamiglia(const string &name) const;

  string getTest() const;

 private:
  MyVector<DeepPtr<EntrataFilm>> listEntrate;
  MyVector<DeepPtr<Utente>> listUtenti;
  MyVector<DeepPtr<Famiglia>> listFamiglie;
  MyVector<DeepPtr<Utente>> listStorico;
  MyVector<DeepPtr<Sala>> listSale;

  string test;
};

#endif  // MODEL_H

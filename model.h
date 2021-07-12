#ifndef MODEL_H
#define MODEL_H

#include "abbonamentoFamigliare.h"
#include "biglietto.h"
#include "deepPtr.h"
#include "myVector.h"
#include "sala.h"

class Model {
 public:
  Model();
  void addEntrata(EntrataFilm *e);
  //  void addAbbonamento(Abbonamento *e);
  //  void addAbbonamentoFam(AbbonamentoFamigliare *e);
  //  void addBiglietto(Biglietto *e);
  void addUtente(Utente *u);
  void addFamiglia(Famiglia *f);
  void addAcquisto(Utente *u);
  void addSala(Sala *s);

  ~Model() = default;

  bool removeEntrata(const EntrataFilm &a);
  bool removeUtente(const Utente &u);
  bool removeFamiglia(const Famiglia &f);
  bool removeAcquisto(const Utente &u);
  bool removeSala(const Sala &s);

  void clearVectorUtenti();
  void clearVectorFamiglie();
  void clearVectorEntrate();
  void cleaVectorSale();

  Utente *getUtente(string cf) const;
  Famiglia *getFamiglia(string name) const;
  EntrataFilm *getEntrataFilm(string cod) const;
  Sala *getSala(string nome) const;

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
};

#endif  // MODEL_H

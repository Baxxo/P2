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
  void addAbbonamento(Abbonamento *a);
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
  void clearVectorAbbonamenti();
  void cleaVectorSale();

  Utente *getUtente(string cf) const;
  Famiglia *getFamiglia(string name) const;
  EntrataFilm *getEntrataFilm(string cod) const;
  Sala *getSala(string nome) const;
  Abbonamento *getAbbonamento(string cod) const;

  const MyVector<DeepPtr<EntrataFilm>> &getListEntrate() const;
  const MyVector<DeepPtr<Utente>> &getListUtenti() const;
  const MyVector<DeepPtr<Famiglia>> &getListFamiglie() const;
  const MyVector<DeepPtr<Sala>> &getListSale() const;
  const MyVector<DeepPtr<Abbonamento>> &getListAbbonamenti() const;

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
  MyVector<DeepPtr<Utente>> listStorico;
  MyVector<DeepPtr<Sala>> listSale;
  MyVector<DeepPtr<Abbonamento>> listAbbonamenti;
};

#endif  // MODEL_H

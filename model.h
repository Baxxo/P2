#ifndef MODEL_H
#define MODEL_H

#include "abbonamentoFamigliare.h"
#include "sala.h"
#include "myVector.h"
#include "deepPtr.h"

class Model {
  public:
    Model(string _test="test");
    void addEntrata(const EntrataFilm & a);
    void addUtente(const Utente & u);
    void addFamiglia(const Famiglia & f);
    void addAcquisto(const Utente &u);

    ~Model() = default;

    bool removeEntrata(const EntrataFilm & a);
    bool removeUtente(const Utente & u);
    bool removeFamiglia(const Famiglia & f);
    bool removeAcquisto(const Utente & u);


    void clearVectorUtenti();
    void clearVectorFamiglie();

    Utente *getUtente(string cf);
    Famiglia & getFamiglia(string cf);
    EntrataFilm & getEntrataFilm();
    Sala  *getSala(string nome);


    const MyVector<DeepPtr<EntrataFilm>> &getListEntrate() const;
    const MyVector<DeepPtr<Utente>> &getListUtenti() const;
    const MyVector<DeepPtr<Famiglia>> &getListFamiglie() const;

    void addUserToFamily(Famiglia& f, Utente *u);

    bool searchCf(const string& cf) const;
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

#endif // MODEL_H

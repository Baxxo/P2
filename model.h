#ifndef MODEL_H
#define MODEL_H

#include "abbonamentoFamigliare.h"
#include "sala.h"
#include "myVector.h"
#include "deepPtr.h"

class Model {
  public:
    Model();
    void addEntrata(const EntrataFilm & a);
    void addUtente(const Utente & u);
    void addFamiglia(const Famiglia & f);
    void addAcquisto(const Utente &u);


    bool removeEntrata(const EntrataFilm & a);
    bool removeUtente(const Utente & u);
    bool removeFamiglia(const Famiglia & f);
    bool removeAcquisto(const Utente & u);


    void clearVectorUtenti();

    Utente *getUtente(string cf);
    Famiglia & getFamiglia(string cf);
    EntrataFilm & getEntrataFilm();
    Sala  *getSala(string nome);


    const MyVector<DeepPtr<EntrataFilm>> &getListEntrate() const;
    const MyVector<DeepPtr<Utente>> &getListUtenti() const;
    const MyVector<DeepPtr<Famiglia>> &getListFamiglie() const;

private:
    MyVector<DeepPtr<EntrataFilm>> listEntrate;
    MyVector<DeepPtr<Utente>> listUtenti;
    MyVector<DeepPtr<Famiglia>> listFamiglie;
    MyVector<DeepPtr<Utente>> listStorico;
    MyVector<DeepPtr<Sala>> listSale;
};

#endif // MODEL_H

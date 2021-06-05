#ifndef MODEL_H
#define MODEL_H

#include "abbonamentoFamigliare.h"
#include "myVector.h"
#include "deepPtr.h"

class Model {
  public:
    Model();
    void addEntrata(const EntrataFilm & a);
    void addUtente(const Utente & u);
    void addFamiglia(const Famiglia & f);

    bool removeEntrata(const EntrataFilm & a);
    bool removeUtente(const Utente & u);
    bool removeFamiglia(const Famiglia & f);

    void clearVectorUtenti();

    Utente *getUtente(string cf);
    Famiglia & getFamiglia(string cf);
    EntrataFilm & getEntrataFilm();

    const MyVector<DeepPtr<EntrataFilm>> &getListEntrate() const;
    const MyVector<DeepPtr<Utente>> &getListUtenti() const;
    const MyVector<DeepPtr<Famiglia>> &getListFamiglie() const;

    void addUserToFamily(Famiglia& f, Utente *u);


private:
    MyVector<DeepPtr<EntrataFilm>> listEntrate;
    MyVector<DeepPtr<Utente>> listUtenti;
    MyVector<DeepPtr<Famiglia>> listFamiglie;
};

#endif // MODEL_H

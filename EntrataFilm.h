#include "Data.h"
#include "Utente.h"
#ifndef ENTRATAFILM
#define ENTRATAFILM 1

class EntrataFilm{

    private:

    Utente* utente;

    Data* data;

    double prezzo;

    public:

    ~EntrataFilm();

    EntrataFilm(Data* d = nullptr, Utente* u = nullptr, double p=7.5);

    virtual double getPrezzo() const;

    string getData() const;

    virtual Utente *getUtente() const;

};
#endif

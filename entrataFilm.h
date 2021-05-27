#include "data.h"
#include "utente.h"
#ifndef ENTRATAFILM
#define ENTRATAFILM 1

class EntrataFilm{

    private:

    Utente* utente;

    Data* data;

    double prezzo;

    public:

    ~EntrataFilm() = default;

    EntrataFilm(Data* d = nullptr, Utente* u = nullptr, double p=7.5);

    virtual double getPrezzo() const;

    Data *getData() const;

    virtual Utente *getUtente() const;

    virtual bool operator ==(const EntrataFilm &o) const;

};
#endif

#include "abbonamento.h"
#ifndef SINGOLO
#define SINGOLO 1

class Singolo: public Abbonamento{

    private:
        int fascia_oraria;

    public:

        Singolo(Data* d, Utente* u, double p=7.5, string c="00000", int e=0, int f=0);

        double getFasciaOraria() const;

        double getPrezzo() const override;

};

#endif

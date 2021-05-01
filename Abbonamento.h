#include "EntrataFilm.h"
#ifndef ABBONAMENTO
#define ABBONAMENTO 1

class Abbonamento: public EntrataFilm{

    private:
        string codice;
        int entrate;


    public:

        Abbonamento(Data*, Utente*, double=7.5, string="00000", int=0);

        int GetEntrate() const;

        double GetPrezzo() const override;




};
#endif

#ifndef SALA
#define SALA 1

#include "utente.h"
using std::string;

class Sala{

    private:
        int righe;
        int colonne;
        string nome_sala;
        Utente *matrix;


    public:

        ~Sala();
        Sala(int r=0, int c=0, string n="null");
        int getRighe() const;
        int getColonne() const;
        string getNomesala() const;

};

#endif

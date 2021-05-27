#include "sala.h"

Sala::Sala(int r, int c, string n)
    : righe(r), colonne(c), nome_sala(n), matrix(new Utente[r*c])
    {}
Sala::~Sala(){
    delete [] matrix;
}
int Sala::getColonne() const{
    return colonne;
}

int Sala::getRighe()const{
    return righe;
}

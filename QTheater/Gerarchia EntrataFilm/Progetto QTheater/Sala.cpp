#include "Sala.h"

Sala::Sala(int r, int c, string nome)
	: righe(r), colonne(c), nome_sala(nome), matrix(new Utente[r*c])
	{}
Sala::~Sala(){
	delete [] matrix;
}
int Sala::GetColonne() const{
	return colonne;
}

int Sala::GetRighe()const{
	return righe;
}


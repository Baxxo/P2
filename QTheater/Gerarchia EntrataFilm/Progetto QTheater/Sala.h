#include <iostream>
#include "Utente.h"
#ifndef SALA
#define SALA 1

using std::string;

class Sala{
	
	private:
		int righe;
		int colonne;
		string nome_sala;
		Utente *matrix;
		
	
	public:
		
		~Sala();
		Sala(int=0, int=0, string="null");
		int GetRighe() const;
		int GetColonne() const;
		
};

#endif

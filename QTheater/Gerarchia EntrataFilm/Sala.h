#include <iostream>
#include <vector>
#ifndef SALA
#define SALA 1
using std::string;
using std::vector;
class Sala{
	
	private:
		int righe;
		int colonne;
		string nome_sala;
		string *matrix;
		
	
	public:
		
		Sala(int=0, int=0, string="null");
		int GetRighe() const;
		int GetColonne() const;
		
};
#endif

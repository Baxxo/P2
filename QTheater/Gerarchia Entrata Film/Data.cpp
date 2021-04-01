#include <iostream>
#include "Data.h"



Data::Data(int gg, int mm, int aa){
	giorno=gg;
	mese=mm;
	anno=aa;
}

int Data::getGiorno() const{
	return giorno;
}

int Data::getMese() const{
	return mese;
}

int Data::getAnno() const{
	return anno;
}


ostream& operator<<(ostream &os, const Data &d){
			return os << d.getGiorno()<< '/' << d.getMese() << '/' << d.getAnno();
		}


#include "Data.h"

using std::string;

Data::Data(int gg, int mm, int aa)

	:giorno(gg), mese(mm), anno(aa)
	
	{}

int Data::getGiorno() const{
	return giorno;
}

int Data::getMese() const{
	return mese;
}

int Data::getAnno() const{
	return anno;
}

string Data::ToString() const {
    return std::to_string(giorno) + "/" + std::to_string(mese) + "/" + std::to_string(anno);
}
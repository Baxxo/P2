#include "data.h"

Data::Data(unsigned int a, unsigned int m, unsigned int g)

    : giorno(a), mese(m), anno(g)

{}

unsigned int Data::getGiorno() const { return giorno; }

unsigned int Data::getMese() const { return mese; }

unsigned int Data::getAnno() const { return anno; }

string Data::ToString() const {
  return std::to_string(giorno) + "/" + std::to_string(mese) + "/" +
         std::to_string(anno);
}

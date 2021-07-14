#include "data.h"
#include <QDebug>

Data::Data(unsigned int a, unsigned int m, unsigned int g)

    : giorno(a),
      mese(m),
      anno(g)

{}

Data::Data(string d) {
  int pos = d.find("/");
  string year = d.substr(0, pos);
  d.erase(0, pos + 1);
  pos = d.find("/");
  string month = d.substr(0, pos);
  d.erase(0, pos + 1);
  pos = d.find("/");
  string day = d.substr(0, pos);
  d.erase(0, pos + 1);

  anno = static_cast<unsigned int>(std::stoi(year));
  mese = static_cast<unsigned int>(std::stoi(month));
  giorno = static_cast<unsigned int>(std::stoi(day));
}

Data::Data(const Data &o) : giorno(o.giorno), mese(o.mese), anno(o.anno) {}

unsigned int Data::getGiorno() const { return giorno; }

unsigned int Data::getMese() const { return mese; }

unsigned int Data::getAnno() const { return anno; }

string Data::ToString() const {
  return std::to_string(giorno) + "/" + std::to_string(mese) + "/" +
         std::to_string(anno);
}

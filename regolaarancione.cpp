#include "regolaarancione.h"

RegolaArancione::RegolaArancione(unsigned int dP, bool m)
    : Regola(dP, m) {}

void RegolaArancione::getRegole(unsigned int &distP, bool &m) {
  distP = getDistanzaPosti();
  m = getMustMascherina();
}

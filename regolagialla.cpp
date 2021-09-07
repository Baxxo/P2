#include "regolagialla.h"

RegolaGialla::RegolaGialla(unsigned int dP, bool m)
    : Regola(dP, m) {}

void RegolaGialla::getRegole(unsigned int &distP, bool &m) {
  distP = getDistanzaPosti();
  m = getMustMascherina();
}

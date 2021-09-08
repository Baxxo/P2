#include "regolarossa.h"

RegolaRossa::RegolaRossa(unsigned int dP, bool m) : Regola(dP, m) {}

void RegolaRossa::getRegole(unsigned int &distP, bool &m) {
  distP = getDistanzaPosti();
  m = getMustMascherina();
}

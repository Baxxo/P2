#include "regolabianca.h"

RegolaBianca::RegolaBianca(unsigned int dP, bool m)
    : Regola(dP, m) {}

void RegolaBianca::getRegole(unsigned int &distP, bool &m) {
  distP = getDistanzaPosti();
  m = getMustMascherina();
}

#include "regolabianca.h"

RegolaBianca::RegolaBianca(unsigned int dP, bool m, bool c): Regola(dP,m,c)
{

}

void RegolaBianca::getRegole(unsigned int &distP, bool &m, bool &c)
{
    distP = getDistanzaPosti();
    m = getMustMascherina();
    c = getCongiuntiVicini();
}

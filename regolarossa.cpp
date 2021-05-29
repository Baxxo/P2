#include "regolarossa.h"

RegolaRossa::RegolaRossa(unsigned int dP, bool m, bool c): Regola(dP,m,c)
{

}

void RegolaRossa::getRegole(unsigned int &distP, bool &m, bool &c)
{
    distP = getDistanzaPosti();
    m = getMustMascherina();
    c = getCongiuntiVicini();
}

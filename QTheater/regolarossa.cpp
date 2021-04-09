#include "regolarossa.h"

RegolaRossa::RegolaRossa(unsigned int dP, bool m, bool c): Regola(dP,m,c)
{

}

void RegolaRossa::getRegole(unsigned int &distP, bool &m)
{
    distP = getDistanzaPosti();
    m = getMustMascherina();
}

#include "regolagialla.h"

RegolaGialla::RegolaGialla(unsigned int dP, bool m, bool c): Regola(dP,m,c)
{

}

void RegolaGialla::getRegole(unsigned int &distP, bool &m, bool c= true);
{
    distP = getDistanzaPosti();
    m = getMustMascherina();
    c = getCongiuntiVicini();
}

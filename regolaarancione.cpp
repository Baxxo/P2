#include "regolaarancione.h"

RegolaArancione::RegolaArancione(unsigned int dP, bool m, bool c): Regola(dP,m,c)
{

}

void RegolaArancione::getRegole(unsigned int &distP, bool &m, bool &c)
{
    distP = getDistanzaPosti();
    m = getMustMascherina();
    c = getCongiuntiVicini();
}

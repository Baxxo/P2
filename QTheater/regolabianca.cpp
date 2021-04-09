#include "regolabianca.h"

RegolaBianca::RegolaBianca(unsigned int dP, bool m, bool c): Regola(dP,m,c)
{

}

void RegolaBianca::getRegole(unsigned int &distP, bool &m)
{
    distP = getDistanzaPosti();
    m = getMustMascherina();
}

#include "regola.h"

unsigned int Regola::getDistanzaPosti() const
{
    return distanzaPosti;
}

void Regola::setDistanzaPosti(unsigned int value)
{
    distanzaPosti = value;
}

Regola::Regola(unsigned int dP, bool m, bool c):distanzaPosti(dP), mustMascherina(m), congiuntiVicini(c)
{

}

bool Regola::getMustMascherina() const
{
    return mustMascherina;
}

void Regola::setMustMascherina(bool value)
{
    mustMascherina = value;
}

#include "regola.h"

bool Regola::getCongiuntiVicini() const
{
  return congiuntiVicini;
}

void Regola::setCongiuntiVicini(bool value)
{
  congiuntiVicini = value;
}

Regola::Regola(unsigned int dP, bool m, bool c):distanzaPosti(dP), mustMascherina(m), congiuntiVicini(c)
{

}

unsigned int Regola::getDistanzaPosti() const
{
    return distanzaPosti;
}

void Regola::setDistanzaPosti(unsigned int value)
{
    distanzaPosti = value;
}

bool Regola::getMustMascherina() const
{
    return mustMascherina;
}

void Regola::setMustMascherina(bool value)
{
    mustMascherina = value;
}

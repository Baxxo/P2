#include "famiglia.h"

Famiglia::Famiglia(unsigned int sz): membri(new Utente*[sz]),size(sz)
{
  for (unsigned int i = 0; i < size; ++i) {
      membri[i] = new Utente();
    }
}

bool Famiglia::hasMembro(Utente *u)
{
  for(unsigned int i=0;i<size;++i){
      if(u->getCodFisc() == membri[i]->getName()){
          return true;
        }
    }
  return false;
}

Utente* &Famiglia::operator[](unsigned int i) const
{
  return membri[i];
}

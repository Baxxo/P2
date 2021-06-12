#include "famiglia.h"

Famiglia::Famiglia(unsigned int sz): membri(new Utente*[sz]),capacity(sz)
{
  for (unsigned int i = 0; i < capacity; ++i) {
      membri[i] = nullptr;
    }
  size = 0;
}

Famiglia::Famiglia(const Famiglia &o) : membri(o.membri), capacity(o.capacity), size(o.size)
{
}

Famiglia::~Famiglia()
{
  delete[] membri;
}

void Famiglia::addMembro(Utente *ut)
{
  membri[size] = ut;
  size++;
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

unsigned int Famiglia::getSize() const
{
  return size;
}

Utente *&Famiglia::operator [](unsigned int i) const{
    if( i > size ) {
        cout << "Index out of bounds" <<endl;
        // return first element.
        return membri[0];
      }

    return membri[i];
}

bool Famiglia::operator ==(const Famiglia &f) const
{
  return f.capacity == capacity && f.size == size && f.membri == membri;
}

Famiglia &Famiglia::operator =(const Famiglia &o)
{
  if(this != &o){
      capacity = o.capacity;
      size = o.size;
      membri = o.membri;
    }
  return *this;
}

Famiglia *Famiglia::clone() const
{
  return new Famiglia(*this);
}

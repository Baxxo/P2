#include "famiglia.h"
#include <stdexcept>

/*
#include <QDebug>*/

#include <iostream>
using namespace std;

Famiglia::Famiglia(unsigned int c): membri(new Utente[c]),capacity(c), size(0)
{}

Famiglia::Famiglia(const Famiglia &o) : membri(new Utente[o.capacity]), capacity(o.capacity), size(o.size)
{
  for(unsigned int i=0;i<o.size;i++){
      membri[i] = o.membri[i];
    }
}

Famiglia::~Famiglia()
{
  delete[] membri;
}

void Famiglia::resize()
{
  capacity *= 2;
  Utente* u = new Utente[capacity];
  for(unsigned int i = 0U; i<size;i++){
      u[i] = membri[i];
      //cout << "Famiglia resize: " << u[i].getCodFisc() << endl;

    }
  delete[] membri;
  membri = u;
  //cout << "esco resize" << endl<<endl;
}

void Famiglia::addMembro(Utente *u)
{
  cout << "inzio--------------" << endl;
  if(size >=capacity){
      resize();
    }
  membri[size] = *u;
  size++;

  for(unsigned int i = 0U; i<size;i++){
      cout << "Famiglia: " << membri[i].getCodFisc() << endl;

    }
  cout << "esco -----------------" << endl<<endl;
}

bool Famiglia::hasMembro(Utente *u)
{
  for(unsigned int i=0;i<size;++i){
      if(u->getCodFisc() == membri[i].getCodFisc()){
          return true;
        }
    }
  return false;
}

unsigned int Famiglia::getSize() const
{
  return size;
}

Utente &Famiglia::operator [](unsigned int i) const{
    if( i >= size ) {
        throw std::out_of_range("Out of range");
      }

    return membri[i];
}

Utente &Famiglia::operator [](int i) const
{
  if( i >= size ) {
      throw std::out_of_range("Out of range");
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

#include "utente.h"

#include <iostream>
using namespace std;

Utente::Utente(std::string n, unsigned int a, std::string cf, std::string num)
  : name(n), age(a), codiceFiscale(cf), phoneNumber(num) {}

Utente::Utente(const Utente &o): name(o.name), age(o.age), codiceFiscale(o.codiceFiscale), phoneNumber(o.phoneNumber) {}


std::string Utente::getName() const
{
    return name;
}

unsigned int Utente::getAge() const
{
    return age;
}

std::string Utente::getCodFisc() const
{
    return codiceFiscale;
}

std::string Utente::getPhoneNumber() const
{
  return phoneNumber;
}

Utente &Utente::operator=(const Utente &o)
{
  if(this != &o){
      name = o.getName();
      age = o.getAge();
      codiceFiscale = o.getCodFisc();
      phoneNumber = o.getPhoneNumber();
    }

  return *this;
}

bool Utente::operator ==(const Utente &o) const
{
  return o.age==age && o.codiceFiscale == codiceFiscale && o.name == name && o.phoneNumber == phoneNumber;
}

bool Utente::operator !=(const Utente &o) const
{
  return o.age!=age && o.codiceFiscale != codiceFiscale && o.name != name && o.phoneNumber != phoneNumber;
}

Utente *Utente::clone() const
{
 return new Utente(*this);
}

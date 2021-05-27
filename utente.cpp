#include "utente.h"

Utente::Utente(std::string n, unsigned int a, std::string cf, std::string num)
    : name(n), age(a), codiceFiscale(cf), phoneNumber(num) {}

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

#include "utente.h"
#include <QDebug>

Utente::Utente(std::string cf, std::string n, std::string s, unsigned int a,
               std::string num)
    : name(n), surname(s), age(a), codiceFiscale(cf), phoneNumber(num) {}

Utente::Utente(const Utente &o)
    : name(o.name),
      surname(o.surname),
      age(o.age),
      codiceFiscale(o.codiceFiscale),
      phoneNumber(o.phoneNumber) {
  qDebug() << "costruito utente copia "
           << QString::fromStdString(codiceFiscale);
}

/// Utente::~Utente() { qDebug() << "distrutto"; }

std::string Utente::getName() const { return name; }

string Utente::getSurname() const { return surname; }

unsigned int Utente::getAge() const { return age; }

std::string Utente::getCodFisc() const { return codiceFiscale; }

std::string Utente::getPhoneNumber() const { return phoneNumber; }

Utente &Utente::operator=(const Utente &o) {
  if (this != &o) {
    name = o.getName();
    age = o.getAge();
    codiceFiscale = o.getCodFisc();
    phoneNumber = o.getPhoneNumber();
  }

  return *this;
}

bool Utente::operator==(const Utente &o) const {
  return o.codiceFiscale == codiceFiscale;
}

bool Utente::operator!=(const Utente &o) const {
  return o.codiceFiscale != codiceFiscale;
}

Utente *Utente::clone() const { return new Utente(*this); }

std::string Utente::toString() const { return name + " " + codiceFiscale; }

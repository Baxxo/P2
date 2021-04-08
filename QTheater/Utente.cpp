#include "Utente.h"

Utente(string n='', unsigned int a=0, string cf='', string num='') 
    : name(n), age(a), codiceFiscale(cf), phoneNumber(num) {}

string getName() const{ return name;}

unsigned int getAge() const {return age;}

string getCodFisc() const { return codiceFiscale;}

string getPhoneNum() const { return phoneNumber;}
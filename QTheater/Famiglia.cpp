#include "Famiglia.h"

Famiglia(Utente* m): membri(m!=nullptr ? m : new Utente()) {};

Utente* getMembri() const{ return membri;}
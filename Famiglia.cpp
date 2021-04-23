#include "Famiglia.h"

Famiglia::Famiglia(Utente *m): membri(m != nullptr ? m : new Utente())
{

}

Utente *Famiglia::getMembri() const
{
    return membri;
}

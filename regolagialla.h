#ifndef REGOLAGIALLA_H
#define REGOLAGIALLA_H
#include "regola.h"

class RegolaGialla: public Regola
{
public:
    RegolaGialla(unsigned int dP=1, bool m=true, bool c= true);
    void getRegole(unsigned int& distP, bool& m, bool& c);
};

#endif // REGOLAGIALLA_H

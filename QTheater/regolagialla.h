#ifndef REGOLAGIALLA_H
#define REGOLAGIALLA_H
#include "regola.h"

class RegolaGialla: public Regola
{
public:
    RegolaGialla(unsigned int dP=1, bool m=true);
    void getRegole(unsigned int& distP, bool& m, bool c= true);
};

#endif // REGOLAGIALLA_H

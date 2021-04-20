#ifndef REGOLAROSSA_H
#define REGOLAROSSA_H
#include "regola.h"

class RegolaRossa : public Regola
{
public:
    RegolaRossa(unsigned int dP=5, bool m=true, bool c= false);
    void getRegole(unsigned int& distP, bool& m, bool c= true);
};

#endif // REGOLAROSSA_H

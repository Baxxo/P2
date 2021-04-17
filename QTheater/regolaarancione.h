#ifndef REGOLAARANCIONE_H
#define REGOLAARANCIONE_H
#include "regola.h"

class RegolaArancione: public Regola
{
public:
    RegolaArancione(unsigned int dP=2, bool m=true, bool c= true);
    void getRegole(unsigned int& distP, bool& m);
};

#endif // REGOLAARANCIONE_H

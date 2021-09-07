#ifndef REGOLABIANCA_H
#define REGOLABIANCA_H
#include "regola.h"

class RegolaBianca : public Regola
{
public:
    RegolaBianca(unsigned int dP=0, bool m=false);
    void getRegole(unsigned int& distP, bool& m);
};

#endif // REGOLABIANCA_H

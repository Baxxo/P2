#include "utente.h"

#include <iostream>

using namespace std;

using std::string;

class Famiglia{
private:
    Utente** membri;
    unsigned int capacity;
    unsigned int size;

public:
    Famiglia(unsigned int sz=1);
    Famiglia(const Famiglia &o);
    ~Famiglia();
    void addMembro(Utente* ut);
    bool hasMembro(Utente* u);
    unsigned int getSize() const;

    Utente *&operator [](unsigned int i) const;
    bool operator ==(const Famiglia& f) const;
    Famiglia& operator =(const Famiglia &o);
};

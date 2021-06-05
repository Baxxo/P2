#include "utente.h"

#include <iostream>

using namespace std;

using std::string;

class Famiglia{
private:
    Utente* membri;
    unsigned int capacity;
    unsigned int size;

    void resize();

public:
    Famiglia(unsigned int c=1);
    Famiglia(const Famiglia &o);
    virtual ~Famiglia();
    void addMembro(Utente* u);
    bool hasMembro(Utente* u);
    unsigned int getSize() const;

    Utente &operator [](unsigned int i) const;
    Utente &operator [](int i) const;
    bool operator ==(const Famiglia& f) const;
    Famiglia& operator =(const Famiglia &o);

    virtual Famiglia *clone() const;
};

#include "Utente.h"

#include <iostream>

using namespace std;

using std::string;

class  Famiglia{
private:
    Utente** membri;
    unsigned int capacity;
    unsigned int size;

public:
    Famiglia(unsigned int sz=1);
    ~Famiglia();
    void addMembro(Utente* ut);
    bool hasMembro(Utente* u);
    unsigned int getSize() const;

    Utente *&operator [](unsigned int i) const;
};

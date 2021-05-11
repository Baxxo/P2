#include "Utente.h"

using std::string;

class Famiglia{
private:
    Utente** membri;
    unsigned int size;
public:
    Famiglia(unsigned int sz=1);
    bool hasMembro(Utente* u);

    Utente* &operator[](unsigned int i) const;
};

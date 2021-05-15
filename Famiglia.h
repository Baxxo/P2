#include "Utente.h"

using std::string;

class Famiglia{
private:
    Utente* membri;
public:
    Famiglia(Utente* m=nullptr);
    Utente *getMembri() const;
};

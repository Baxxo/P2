#include "Utente.h"

using std::string;

class Famiglia{
private:
    Utente* membri; //deve diventare un vector
public:
    Famiglia(Utente* m=nullptr);
    Utente *getMembri() const;
};

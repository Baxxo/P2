#include <string>
#ifndef UTENTE
#define UTENTE 1

using std::string;

class Utente{
private:
    string name;
    unsigned int age;
    string codiceFiscale;
    string phoneNumber;
public:
    Utente(string n="", unsigned int a=0, string cf="", string num="");
    Utente(const Utente &o);
    virtual ~Utente() = default;

    string getName() const;

    unsigned int getAge() const;

    string getCodFisc() const;

    string getPhoneNumber() const;

    Utente &operator= (const Utente& o);
    bool operator ==(const Utente &o) const;
    bool operator !=(const Utente &o) const;

    virtual Utente *clone() const;
};
#endif

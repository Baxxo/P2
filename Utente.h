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

    string getName() const;

    unsigned int getAge() const;

    string getCodFisc() const;

    string getPhoneNumber() const;
};
#endif

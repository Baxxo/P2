#include "utente.h"

#include <iostream>

//using namespace std;

using std::string;
using std::ostream;

class Famiglia{
private:
    Utente** membri;
    unsigned int capacity;
    unsigned int size;
    string name;

    void resize();

public:
    Famiglia(string _name = "", unsigned int c=1);
    Famiglia(const Famiglia &o);
    virtual ~Famiglia();
    void addMembro(Utente* u);
    void removeMembro(Utente* u);
    bool hasMembro(Utente* u);
    unsigned int getSize() const;

    Utente* operator[](unsigned int i) const;
    Utente* operator[](int i) const;
    bool operator ==(const Famiglia& f) const;
    bool operator !=(const Famiglia& f) const;
    Famiglia& operator =(const Famiglia &o);

    virtual Famiglia *clone() const;

    string getName() const;
    void setName(const string &value);

    string toString() const;
};

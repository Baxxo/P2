#include <iostream>
#ifndef DATA
#define DATA 1

using std::ostream;
using std::string;

class Data{
    private:
        unsigned int  giorno;
        unsigned int  mese;
        unsigned int  anno;

    public:

        Data(unsigned int a= 1990, unsigned int  m = 1, unsigned int  g =1);

        unsigned int  getGiorno() const;

        unsigned int  getMese() const;

        unsigned int  getAnno() const;

        string ToString() const;

        //friend ostream& operator<<(ostream &os, const Data& dt);


};
#endif

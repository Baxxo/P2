#ifndef DATA
#define DATA
#include <iostream>

using std::ostream;
using std::string;

class Data {
 private:
  unsigned int giorno;
  unsigned int mese;
  unsigned int anno;

 public:
  Data(unsigned int a = 1990, unsigned int m = 1, unsigned int g = 1);
  virtual ~Data() = default;

  unsigned int getGiorno() const;

  unsigned int getMese() const;

  unsigned int getAnno() const;

  string ToString() const;
};
#endif

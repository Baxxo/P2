#ifndef ABBONAMENTO
#define ABBONAMENTO
#include "entrataFilm.h"
using std::string;

class Abbonamento : public EntrataFilm {
 private:
  int entrate;

 public:
  Abbonamento(Data *d = new Data(), string u = "", double p = 7.5,
              string cod = "00000", int entr = 0);

  Abbonamento(const Abbonamento &o);

  ~Abbonamento() = default;

  double getPrezzo() const override;

  Abbonamento &operator=(const Abbonamento &o);

  Abbonamento *clone() const override;

  string toString() const override;

  int getEntrate() const;

  void removeOneEntrata();
};
#endif

#ifndef ENTRATAFILM
#define ENTRATAFILM
#include "data.h"

using std::string;

class EntrataFilm {
 private:
  string codice;
  string utente;
  Data *data;
  double prezzo;

 public:
  EntrataFilm(string cod = "0", Data *d = nullptr, string u = "",
              double p = 7.5);
  EntrataFilm(const EntrataFilm &o);

  virtual ~EntrataFilm() = default;

  virtual double getPrezzo() const;

  virtual Data *getData() const;

  virtual string getUtente() const;

  virtual bool operator==(const EntrataFilm &o) const;

  virtual bool operator!=(const EntrataFilm &o) const;

  virtual EntrataFilm &operator=(const EntrataFilm &o);

  virtual EntrataFilm *clone() const;

  virtual string toString() const;

  virtual string getCodice() const;
};
#endif

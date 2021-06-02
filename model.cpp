#include "model.h"


Model::Model(){}

void Model::addEntrata(const EntrataFilm &a) {
  listEntrate.push_back(DeepPtr<EntrataFilm>(a));
}

void Model::addUtente(const Utente &u) {
  listUtenti.push_back(DeepPtr<Utente>(u));
}

void Model::addFamiglia(const Famiglia &f) {
  listFamiglie.push_back(DeepPtr<Famiglia>(f));
}

bool Model::removeEntrata(const EntrataFilm &a) {
  return listEntrate.remove(a);
}

bool Model::removeUtente(const Utente &u) {
  return listUtenti.remove(u);
}

bool Model::removeFamiglia(const Famiglia &f) {
  return listFamiglie.remove(f);
}

Utente* Model::getUtente(string cf) {

  for (auto it = listUtenti.begin(); it != listUtenti.end(); ++it) {
      //cout << (*it)->getName() << endl;
      //cout << (*it)->getCodFisc() << " = "<< cf << endl;
      if((*it)->getCodFisc() == cf){
          //cout << (*it)->getName() << endl;
          return new Utente(**it);
        }
  }
  return nullptr;
}

const MyVector<DeepPtr<EntrataFilm> > &Model::getListEntrate() const
{
  return listEntrate;
}

const MyVector<DeepPtr<Utente>> &Model::getListUtenti() const
{
  return listUtenti;
}

const MyVector<DeepPtr<Famiglia>> &Model::getListFamiglie() const
{
  return listFamiglie;
}

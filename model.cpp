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

void Model::addAcquisto(const Utente &u)
{
    listStorico.push_back(DeepPtr<Utente>(u));
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

bool Model::removeAcquisto(const Utente &u)
{
    return listStorico.remove(u);
}

void Model::clearVectorUtenti()
{
  listUtenti.clear();
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

Sala *Model::getSala(string nome)
{
    for (auto it = listSale.begin(); it != listSale.end(); ++it) {
        //cout << (*it)->getName() << endl;
        //cout << (*it)->getCodFisc() << " = "<< cf << endl;
        if((*it)->getNomesala() == nome){
            //cout << (*it)->getName() << endl;
            return new Sala(**it);
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

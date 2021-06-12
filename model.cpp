#include "model.h"

/*
#include <iostream>
using namespace std;
*/


Model::Model(string _test):test(_test){
}

void Model::addEntrata(const EntrataFilm &a) {
  listEntrate.push_back(DeepPtr<EntrataFilm>(a));
}

void Model::addUtente(const Utente &u) {
  listUtenti.push_back(DeepPtr<Utente>(u));

  /*cout << "model add utente"<<endl;
  for (auto it = listUtenti.begin(); it != listUtenti.end(); ++it) {
      cout << (*it)->getName() << " " <<  (*it)->getCodFisc() << endl;
  }
  cout <<endl<<endl<<endl<<endl;*/
}

void Model::addFamiglia(const Famiglia &f) {
  listFamiglie.push_back(DeepPtr<Famiglia>(f));


  /*for (auto it = listFamiglie.begin(); it != listFamiglie.end(); ++it) {
      cout << (*it)->getName() << endl;
  }
  cout <<endl<<endl<<endl<<endl;*/
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

void Model::clearVectorUtenti()
{
  listUtenti.clear();
}

void Model::clearVectorFamiglie()
{
  listFamiglie.clear();
}

Utente* Model::getUtente(string cf) {

  auto it = listUtenti.cbegin();

  for (; it != listUtenti.cend(); ++it) {
      if((*it)->getCodFisc() == cf){
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

void Model::addUserToFamily(Famiglia &f, Utente *u)
{
  f.addMembro(u);
}

bool Model::searchCf(const string& cf) const
{
  if(!listUtenti.isEmpty()){
      auto it = listUtenti.csearch(Utente(cf));
      return (*it)->getCodFisc() == cf;
    }
  return false;
}

bool Model::searchNameFamiglia(const string &name) const
{
  if(!listFamiglie.isEmpty()){
      auto it = listFamiglie.csearch(Famiglia(name));
      return (*it)->getName() == name;
    }
  return false;
}

string Model::getTest() const
{
  return test;
}

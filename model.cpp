#include "model.h"
#include <QDebug>

Model::Model(string _test) : test(_test) {}

void Model::addEntrata(const EntrataFilm &a) {
  listEntrate.push_back(DeepPtr<EntrataFilm>(a));
}

void Model::addUtente(const Utente &u) {
  listUtenti.push_back(DeepPtr<Utente>(u));
}

void Model::addFamiglia(const Famiglia &f) {
  listFamiglie.push_back(DeepPtr<Famiglia>(f));
}

void Model::addAcquisto(const Utente &u) {
  listStorico.push_back(DeepPtr<Utente>(u));
}

void Model::addSala(const Sala &s) { listSale.push_back(DeepPtr<Sala>(s)); }

bool Model::removeEntrata(const EntrataFilm &a) {
  return listEntrate.remove(a);
}

bool Model::removeUtente(const Utente &u) { return listUtenti.remove(u); }

bool Model::removeFamiglia(const Famiglia &f) { return listFamiglie.remove(f); }

bool Model::removeAcquisto(const Utente &u) { return listStorico.remove(u); }

bool Model::removeSala(const Sala &s) { return listSale.remove(s); }

void Model::clearVectorUtenti() { listUtenti.clear(); }

void Model::clearVectorFamiglie() { listFamiglie.clear(); }

void Model::cleaVectorSale() { listSale.clear(); }

Utente *Model::getUtente(string cf) {

  auto it = listUtenti.cbegin();

  for (; it != listUtenti.cend(); ++it) {
    if ((*it)->getCodFisc() == cf) {
      return new Utente(**it);
    }
  }
  return nullptr;
}

Sala *Model::getSala(string nome) {
  for (auto it = listSale.begin(); it != listSale.end(); ++it) {
    // cout << (*it)->getName() << endl;
    // cout << (*it)->getCodFisc() << " = "<< cf << endl;
    if ((*it)->getNomesala() == nome) {
      // cout << (*it)->getName() << endl;
      return new Sala(**it);
    }
  }
  return nullptr;
}

const MyVector<DeepPtr<EntrataFilm>> &Model::getListEntrate() const {
  return listEntrate;
}

const MyVector<DeepPtr<Utente>> &Model::getListUtenti() const {
  return listUtenti;
}

const MyVector<DeepPtr<Famiglia>> &Model::getListFamiglie() const {
  return listFamiglie;
}

const MyVector<DeepPtr<Sala>> &Model::getListSale() const { return listSale; }

void Model::addUserToFamily(Famiglia &f, Utente *u) { f.addMembro(u); }

bool Model::searchCf(const string &cf) const {
  if (!listUtenti.isEmpty()) {
    auto it = listUtenti.csearch(Utente(cf));
    return (*it)->getCodFisc() == cf;
  }
  return false;
}

bool Model::searchNameFamiglia(const string &name) const {
  if (!listFamiglie.isEmpty()) {
    auto it = listFamiglie.csearch(Famiglia(name));
    return (*it)->getName() == name;
  }
  return false;
}

string Model::getTest() const { return test; }

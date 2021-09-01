#include "model.h"
//#include <QDebug>

Model::Model() {}

void Model::addEntrata(EntrataFilm *e) {
  listEntrate.push_back(DeepPtr<EntrataFilm>(e));
}

void Model::addUtente(Utente *u) { listUtenti.push_back(DeepPtr<Utente>(u)); }

void Model::addFamiglia(Famiglia *f) {
  listFamiglie.push_back(DeepPtr<Famiglia>(f));
}

void Model::addSala(Sala *s) { listSale.push_back(DeepPtr<Sala>(s)); }

bool Model::removeEntrata(const string &e) {
  bool chk = false;
  //  int i = 0;
  //  for (auto it = listEntrate.cbegin(); it != listEntrate.cend(); ++it) {
  //    if ((**it).getCodice() == e.toStdString()) {
  //      chk = listEntrate.erase(listEntrate.begin() + i);
  //    }
  //    i++;
  //  }
  for (int i = 0; i < listEntrate.getSize(); ++i) {
    if (listEntrate[i]->getCodice() == e) {
      chk = listEntrate.erase(listEntrate.begin() + i);
    }
  }
  return chk;
}

bool Model::removeUtente(const Utente &u) {
  int i = 0;
  for (auto it = listUtenti.cbegin(); it != listUtenti.cend(); ++it) {
    i++;
    if ((**it).getCodFisc() == u.getCodFisc()) {
      return listUtenti.erase(listUtenti.begin() + i);
    }
  }
  return false;
}

bool Model::removeFamiglia(const Famiglia &f) {
  int i = 0;
  for (auto it = listFamiglie.cbegin(); it != listFamiglie.cend(); ++it) {
    i++;
    if ((**it).getName() == f.getName()) {
      return listFamiglie.erase(listFamiglie.begin() + i);
    }
  }
  return false;
}

bool Model::removeSala(const Sala &s) {
  int i = 0;
  for (auto it = listSale.cbegin(); it != listSale.cend(); ++it) {
    i++;
    if ((**it).getNomesala() == s.getNomesala()) {
      return listSale.erase(listSale.begin() + i);
    }
  }
  return false;
}

void Model::clearVectorUtenti() { listUtenti.clear(); }

void Model::clearVectorFamiglie() { listFamiglie.clear(); }

void Model::clearVectorEntrate() { listEntrate.clear(); }

void Model::cleaVectorSale() { listSale.clear(); }

Utente *Model::getUtente(string cf) const {
  auto it = listUtenti.cbegin();

  for (; it != listUtenti.cend(); ++it) {
    if ((*it)->getCodFisc() == cf) {
      return new Utente(**it);
    }
  }
  return nullptr;
}

Famiglia *Model::getFamiglia(string name) const {
  auto it = listFamiglie.cbegin();

  for (; it != listFamiglie.cend(); ++it) {
    if ((*it)->getName() == name) {
      return new Famiglia(**it);
    }
  }
  return nullptr;
}

EntrataFilm *Model::getEntrataFilm(string cod) const {
  auto it = listEntrate.cbegin();

  for (; it != listEntrate.cend(); ++it) {
    if ((*it)->getCodice() == cod) {
      if (dynamic_cast<Biglietto *>(&(**it))) {
        return new Biglietto(*dynamic_cast<Biglietto *>(&(**it)));
      } else if (dynamic_cast<Abbonamento *>(&(**it))) {
        if (dynamic_cast<AbbonamentoFamigliare *>(&(**it))) {
          return new AbbonamentoFamigliare(
              *dynamic_cast<AbbonamentoFamigliare *>(&(**it)));
        } else {
          return new Abbonamento(*dynamic_cast<Abbonamento *>(&(**it)));
        }
      }
    }
  }
  return nullptr;
}

Sala *Model::getSala(string nome) const {
  for (auto it = listSale.cbegin(); it != listSale.cend(); ++it) {
    if ((*it)->getNomesala() == nome) {
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
    auto it = listUtenti.csearch(new Utente(cf));
    return (*it)->getCodFisc() == cf;
  }
  return false;
}

bool Model::searchNameFamiglia(const string &name) const {
  if (!listFamiglie.isEmpty()) {
    auto it = listFamiglie.csearch(new Famiglia(name));
    return (*it)->getName() == name;
  }
  return false;
}

bool Model::searchEntrata(const string &cod) const {
  bool trovato = false;
  if (!listEntrate.isEmpty()) {
    for (auto it = listEntrate.cbegin(); it != listEntrate.cend(); ++it) {
      if ((*it)->getCodice() == cod) trovato = true;
    }
  }
  return trovato;
}

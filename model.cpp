#include "model.h"

Model::Model() {}

void Model::addEntrata(EntrataFilm *e) {
  listEntrate.push_back(DeepPtr<EntrataFilm>(e));
}

/*void Model::addAbbonamento(Abbonamento *e) {
  DeepPtr<EntrataFilm> tmp(new Abbonamento(*e));
  listEntrate.push_back(tmp);
}

void Model::addAbbonamentoFam(AbbonamentoFamigliare *e) {
  DeepPtr<EntrataFilm> tmp(new AbbonamentoFamigliare(*e));
  listEntrate.push_back(tmp);
}

void Model::addBiglietto(Biglietto *e) {
  DeepPtr<EntrataFilm> tmp(new Biglietto(*e));
  listEntrate.push_back(tmp);
}
*/
void Model::addUtente(Utente *u) {
  //  qDebug() << "addUtente " << QString::fromStdString(u->getCodFisc());
  listUtenti.push_back(DeepPtr<Utente>(u));
  //  qDebug() << "--";
}

void Model::addFamiglia(Famiglia *f) {
  listFamiglie.push_back(DeepPtr<Famiglia>(f));
}

void Model::addAcquisto(Utente *u) {
  listStorico.push_back(DeepPtr<Utente>(u));
}

void Model::addSala(Sala *s) { listSale.push_back(DeepPtr<Sala>(s)); }

bool Model::removeEntrata(const EntrataFilm &a) {
  DeepPtr<EntrataFilm> tmp(new EntrataFilm(a));
  return listEntrate.remove(tmp);
}

bool Model::removeUtente(const Utente &u) {
  DeepPtr<Utente> tmp(new Utente(u));
  return listUtenti.remove(tmp);
}

bool Model::removeFamiglia(const Famiglia &f) {
  DeepPtr<Famiglia> tmp(new Famiglia(f));
  return listFamiglie.remove(tmp);
}

bool Model::removeAcquisto(const Utente &u) {
  DeepPtr<Utente> tmp(new Utente(u));
  return listStorico.remove(tmp);
}

bool Model::removeSala(const Sala &s) {
  DeepPtr<Sala> tmp(new Sala(s));
  return listSale.remove(tmp);
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

Famiglia *Model::getFamiglia(std::string name) const {
  auto it = listFamiglie.cbegin();

  for (; it != listFamiglie.cend(); ++it) {
    if ((*it)->getName() == name) {
      return new Famiglia(**it);
    }
  }
  return nullptr;
}

EntrataFilm *Model::getEntrataFilm(std::string cod) const {
  auto it = listEntrate.cbegin();

  for (; it != listEntrate.cend(); ++it) {
    if ((*it)->getCodice() == cod) {
      return new EntrataFilm(**it);
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
  //  qDebug() << "searchCf";
  if (!listUtenti.isEmpty()) {
    //    qDebug() << "not empty";
    auto it = listUtenti.csearch(new Utente(cf));
    return (*it)->getCodFisc() == cf;
  }
  //  qDebug() << "empty";
  return false;
}

bool Model::searchNameFamiglia(const string &name) const {
  if (!listFamiglie.isEmpty()) {
    auto it = listFamiglie.csearch(new Famiglia(name));
    return (*it)->getName() == name;
  }
  return false;
}

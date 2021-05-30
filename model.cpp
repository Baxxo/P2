#include "model.h"

#include <iostream>
using namespace std;

Model::Model(){}

void Model::addEntrata(const EntrataFilm * a) {
  listEntrate.push_back(a);
}

void Model::addUtente(const Utente * u) {
  listUtenti.push_back(u);
}

void Model::addFamiglia(const Famiglia * f) {
  listFamiglie.push_back(f);
}

bool Model::removeEntrata(const EntrataFilm * a) {
  return listEntrate.remove( * a);
}

bool Model::removeUtente(const Utente * u) {
  return listUtenti.remove( * u);
}

bool Model::removeFamiglia(const Famiglia * f) {
  return listFamiglie.remove( * f);
}

Utente * Model::getUtente(string cf) {

  auto it = listUtenti.begin();
  auto it_end = listUtenti.end();

  for (; it != it_end; ++it) {
      cout << (*it).getName() << endl;
  }
  return new Utente();
}

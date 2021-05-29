#include "model.h"

Model::Model() : f(new Famiglia(3))
{}

void Model::addEntrata(const EntrataFilm *a)
{
  if(a != nullptr){
      listAbbonamento.push_back(a);
      //cout << "inserito: " << listAbbonamento[listAbbonamento.getSize()-1].getUtente()->getName() << " fine" <<std::endl;//
    }
}

bool Model::removeEntrata(EntrataFilm *a)
{
  return listAbbonamento.remove(*a);
}

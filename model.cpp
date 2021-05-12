#include "model.h"

Model::Model() : f(new Famiglia(3))
{}

void Model::addEntrata(const EntrataFilm *a)
{
  if(a != nullptr){
      listAbbonamento.add(a);
      //cout << "inserito: " << listAbbonamento[listAbbonamento.getSize()-1].getUtente()->getName() << " fine" <<std::endl;//
    }
}

void Model::removeEntrata(EntrataFilm *a)
{
  listAbbonamento.remove(*a);

  //cout << endl<< endl;

  //cout <<std::endl<< "size abb: " << listAbbonamento.getSize()<<std::endl;
/*
  for (unsigned int i = 0; i < listAbbonamento.getSize(); i++) {
      cout << "rimane "<<listAbbonamento[i].getUtente()->getName() << endl;
    }*/
}

#include "Mainwindow.h"

#include "model.h"
//#include "abbonamentoFamigliare.h"

#include <QApplication>

int main(/*int argc, char *argv[]*/)
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();

  Model model;

  EntrataFilm* a1 = new Abbonamento(new Data(2021u,5u,5u),new Utente("Utente1",21,"abcdef12a34g567h","1234567890"),10,"1",10);
  EntrataFilm* a2 = new Abbonamento(new Data(2021u,5u,5u),new Utente("Utente2",21,"abcdef12a34g567h","1234567890"),50,"2",1);

  Famiglia f1(2);
  Utente * u1 = new Utente("Padre",21,"abcdef12a34g567h","1234567890");
  Utente * u2 = new Utente("Utente5",21,"abcdef12a34g567h","1234567890");
  Utente * u3 = new Utente("Utente6",21,"abcdef12a34g567h","1234567890");
  f1.addMembro(u1);
  f1.addMembro(u2);
  f1.addMembro(u3);
/*
  cout <<"inizio ciclo: " << f1.getSize() << endl;
  for(unsigned int i=0;i<f1.getSize();++i){
      cout << f1[i]->getName() << endl;
    }
  cout <<"fine ciclo" << endl << endl;*/

  EntrataFilm* a5 = new AbbonamentoFamigliare(new Data(),u1,&f1,10,"5",10);

  EntrataFilm* e = new EntrataFilm(new Data(2021u,5u,5u),new Utente("Utente5",21,"abcdef12a34g567h","1234567890"));

  model.addEntrata(a1);
  model.addEntrata(a2);
  model.addEntrata(e);
  model.addEntrata(a5);

  model.removeEntrata(a2);
}

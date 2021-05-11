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
  EntrataFilm* a2 = new Abbonamento(new Data(2021u,5u,5u),new Utente("Utente2",21,"abcdef12a34g567h","1234567890"),10,"2",10);
  EntrataFilm* a3 = new Abbonamento(new Data(2021u,5u,5u),new Utente("Utente3",21,"abcdef12a34g567h","1234567890"),10,"3",10);
  EntrataFilm* a4 = new Abbonamento(new Data(2021u,5u,5u),new Utente("Utente4",21,"abcdef12a34g567h","1234567890"),10,"4",10);

  EntrataFilm* e = new EntrataFilm(new Data(2021u,5u,5u),new Utente("Utente5",21,"abcdef12a34g567h","1234567890"));
  model.addEntrata(a1);
  model.addEntrata(a2);
  model.addEntrata(a3);
  model.addEntrata(a4);
  model.addEntrata(e);

  model.removeEntrata(a3);
}

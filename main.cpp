/*#include "mainwindow.h"
#include "controller.h"
*/


#include "model.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    /*MainWindow m;
    Controller c;
    c.setView(&m);
    m.setController(&c);
    m.show();*/

    Model m;
    Utente* u1 = new Utente("Utente1",1,"asdasdasd","123");
    Utente* u2 = new Utente("Utente2",1,"qweqweqwe","456");
    Utente* u3 = new Utente("Utente3",1,"zxczxc","789");


    m.addUtente(u1);
    m.addUtente(u2);
    m.addUtente(u3);

    m.getUtente("");
    /*return a.exec();*/
}

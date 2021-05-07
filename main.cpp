#include "Mainwindow.h"
#include "Utente_View.h"
#include "famiglia_view.h"
//#include "controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Utente_View u;
    //Controller c;
    u.show();
    return a.exec();
}

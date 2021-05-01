#include "Mainwindow.h"
#include "Utente_View.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Utente_View u;
    u.show();
    return a.exec();
}

#include "controller.h"
#include <iostream>

Controller::Controller(QObject *parent) :
    QObject(parent) //view(new Utente_View), button(new QPushButton)
{
    //connect(button, SIGNAL(clicked()),this, SLOT(pushButton()));
}

void Controller::setView(Utente_View *v)
{
    view=v;
}

/*void Controller::pushButton()
{
    std::cout<<"ciao";
}
*/

#include "controller.h"
#include <iostream>

using std::string;
Controller::Controller(QObject *parent) :
     QObject(parent), isAdmin(false), isClient(false), isUtente(false)
{
    QFile file(QDir::homePath() + "/Desktop/P2-feature-MainWindow/json/test.json");
    QString settings;

    if (!file.open(QIODevice::ReadOnly)) {
      qDebug() << "File open error";
    } else {

        settings = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(settings.toUtf8()));

        qDebug()<< "sta succedendo";
        arrayUtenti= new QJsonArray;
        *arrayUtenti= doc.array();
    }
}

void Controller::openAdmin()
{
    if(isAdmin){
        admin->show();
    }
    else{
    admin = new Admin();
    admin->show();
    isAdmin=true;
    }

}

void Controller::openClient()
{
    if(isClient){
        client->show();
    }
    else{
        client = new Client();
        client->show();
        isClient=true;
    }
    
}

void Controller::openUtente()
{
    if(isUtente){
        utente->show();
    }
    else{
        utente= new Utente_View;
        utente->show();
    }
}

void Controller::annullaUtente()
{
    std::cout<<"test";
}

void Controller::salvaUtente()
{
    QFile file(QDir::homePath() + "/Desktop/P2-feature-MainWindow/json/test.json");

    if (!file.open(QIODevice::ReadWrite)) {
      qDebug() << "File open error";
    } else {


        arrayUtenti->append("test");
        QJsonDocument writeDoc;
        writeDoc.setArray(*arrayUtenti);

        file.write(writeDoc.toJson());

    }
    file.close();
}

void Controller::setView(MainWindow *v)
{
    view=v;
}


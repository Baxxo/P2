#include "controller.h"

//QFile file(QDir::homePath() + "/Desktop/P2-feature-MainWindow/json/test.json");

using std::string;
QString Controller::getPathJson() const
{
  return pathJson;
}

Controller::Controller(QObject *parent) :
  QObject(parent), isAdmin(false), isClient(false), isUtente(false), isFamiglia(false), pathJson(QDir::currentPath()+ "/test.json" )
{
    readUtenti();
}

void Controller::openAdmin()
{
    if(isAdmin){
        admin->show();
    }
    else{
    admin = new Admin(this);
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
        client = new Client(this);
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
        utente= new Utente_View(this);
        utente->show();
        isUtente=true;
    }
}

void Controller::openFamiglia()
{
    if(isFamiglia){
        famiglia->show();
    }
    else{
        famiglia= new Famiglia_View(this);
        famiglia->show();
        isFamiglia= false;
    }
}

void Controller::listaUtenti()
{
    QComboBox* menu= new QComboBox;
    QJsonObject::iterator a= objUtenti->begin();
    for(int i=0; i<objUtenti->size();i++){
        menu->addItem(a.key());
        a++;
    }

    famiglia->setMenu(menu);
    famiglia->showMenu();
    //QString arrayUtenti

}

void Controller::annullaUtente()
{
    qDebug() << "test";
}




void Controller::salvaUtente()
{
    QFile file(pathJson);

    if (!file.open(QIODevice::WriteOnly)) {
      qDebug() << "File open error" << file.errorString();
    } else {

        QJsonObject newUser;
        newUser.insert("name", utente->getName());
        newUser.insert("CF", utente->getCF());
        newUser.insert("age", utente->getAge());
        newUser.insert("tel.Num", utente->getNumTel());
        objUtenti->insert(utente->getCF(), newUser);
        QJsonDocument writeDoc;
        writeDoc.setObject(*objUtenti);

        file.write(writeDoc.toJson());

    }
    file.close();
}

void Controller::setView(MainWindow *v)
{
    view=v;
}

void Controller::readUtenti()
{

    QFile file(pathJson);
    QString settings;

    if (!file.open(QIODevice::ReadOnly)) {
      qDebug() << "File open error";
    } else {

        settings = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(settings.toUtf8()));

        //qDebug()<< "sta succedendo";
        objUtenti= new QJsonObject;
        *objUtenti=doc.object();

    }
}


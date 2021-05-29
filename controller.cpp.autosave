#include "controller.h"

//QFile file(QDir::homePath() + "/Desktop/P2-feature-MainWindow/json/test.json");

using std::string;
QString Controller::getPathJsonUtenti() const
{
  return pathJsonUtenti;
}

Controller::Controller(QObject *parent) :
  QObject(parent), isAdmin(false), isClient(false), isUtente(false), isFamiglia(false), pathJsonUtenti(QDir::currentPath()+ "/utenti.json" ), pathJsonFamiglie(QDir::currentPath()+ "/famiglie.json" )
{
    readUtenti();
    readFamiglie();
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
    bool found=false;
    int i=0;
    QString key;
    //QComboBox* menu= new QComboBox;
    QJsonObject::iterator a= objUtenti->begin();
    while(!found || i<objUtenti->size()){
        if(a.key()==famiglia->getSearch()){
            key= a.key();
            found=true;
        }
        i++;
        a++;
    }
    if(!found){
        key= "CF non esistente, creare nuovo utente";
    }
    //menu->addItem(key);
    famiglia->addLista(key);
    //famiglia->showMenu();
    //QString arrayUtenti

}

void Controller::annullaUtente()
{
    qDebug() << "test";
}




void Controller::salvaUtente()
{
    QFile file(pathJsonUtenti);

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

void Controller::salvaFamiglia()
{
    QFile file(pathJsonFamiglie);

    if (!file.open(QIODevice::WriteOnly)) {
      qDebug() << "File open error" << file.errorString();
    } else {

        QJsonObject newUser;
        for(int i=0; i<famiglia->getListSize(); i++){
            newUser.insert(famiglia->getItem(i), famiglia->getItem(i));
        }
        qDebug() << newUser.length() << famiglia->getListSize();
        objFamiglie->insert(famiglia->getFamilyName(), newUser);
        QJsonDocument writeDoc;
        writeDoc.setObject(*objFamiglie);

        file.write(writeDoc.toJson());
          qDebug() << "test";

    }
    file.close();
}

void Controller::setView(MainWindow *v)
{
    view=v;
}

void Controller::readUtenti()
{

    QFile file(pathJsonUtenti);
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

void Controller::readFamiglie()
{

    QFile file(pathJsonFamiglie);
    QString settings;

    if (!file.open(QIODevice::ReadOnly)) {
      qDebug() << "File open error";
    } else {

        settings = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(settings.toUtf8()));

        //qDebug()<< "sta succedendo";
        objFamiglie= new QJsonObject;
        *objFamiglie=doc.object();

    }
}


#include "controller.h"
#include <QFileDialog>
using std::string;


//QFile file(QDir::homePath() + "/Desktop/P2-feature-MainWindow/json/test.json");

Controller::Controller(QObject *parent, Model *m) :
  QObject(parent), model(m), isAdmin(false), isClient(false), isUtente(false), isFamiglia(false), pathJsonUsers(QDir::currentPath()+ "/users.json" )
{}

QString Controller::getPathJson() const
{
  return pathJsonUsers;
}

void Controller::openAdmin()
{
    if(isAdmin){
        admin->show();
    }
    else{
        admin = new Admin(this);
        for (auto it = model->getListUtenti().cbegin(); it != model->getListUtenti().cend(); ++it) {
            admin->addUtente(QString::fromUtf8(((*it)->getSurname() + " " + (*it)->getName()).c_str()));
        }
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

    QString fileName = QFileDialog::getOpenFileName(nullptr, "Seleziona json per salavre utenti", "", "json(*.json)");
    QFile file(fileName);

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
  view = v;
}

void Controller::readUtenti()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Carica json Utenti", "", "json(*.json)");
    pathJsonUsers = fileName;
    QFile file(fileName);
    QString settings;

    if (!file.open(QIODevice::ReadOnly)) {
      qDebug() << "File open error";
    } else {

        settings = file.readAll();

        QJsonDocument doc(QJsonDocument::fromJson(settings.toUtf8()));
        QJsonObject jObj = doc.object();

        QVariantMap mainMap = jObj.toVariantMap();
        QVariantList localList = mainMap["Utenti"].toList();

        Utente *u;
        for(int i=0;i<localList.length();++i){
            QVariantMap map = localList[i].toMap();
            u = new Utente(map["name"].toString().toUtf8().constData(),
                map["surname"].toString().toUtf8().constData(),
                map["age"].toInt(),
                map["CF"].toString().toUtf8().constData(),
                map["tel.Num"].toString().toUtf8().constData());
            model->addUtente(*u);
          }

        /*Utente* ut = model->getUtente("bssmtt98p06asd3");
        string n = ut->getName();
        QString str = QString::fromUtf8(n.c_str());
        qDebug() <<"nome " << str;*/

        view->changeMenu();

      }
}

void Controller::readFimiglie()
{

}

void Controller::readEntrata()
{

}


#include "controller.h"
#include <QFileDialog>
using std::string;

Controller::Controller(QObject *parent, Model *m) :
  QObject(parent), model(m), isAdmin(false), isClient(false), isUtente(false), isFamiglia(false), pathJsonUsers("")
{}

QString Controller::getPathJson() const
{
  return pathJsonUsers;
}

bool Controller::getIsAdmin() const
{
  return isAdmin;
}

void Controller::setIsAdmin(bool value)
{
  isAdmin = value;
  if(isAdmin){
      view->changeTitleAdmin(QString("Aggiorna admin"));
    }else{
      view->changeTitleAdmin(QString("Admin"));
    }
}

void Controller::loadUsersinView() const
{
  admin->clearListUtenti();
  for (auto it = model->getListUtenti().cbegin(); it != model->getListUtenti().cend(); ++it) {
      admin->addUtente(QString::fromUtf8(((*it)->getSurname() + " " + (*it)->getName()).c_str()));
    }
}

void Controller::openError(QString message)
{
  if(err){
      err->setMessage(message);
    }else{
      err = new ErrorDisplay(nullptr,message);
    }
  err->show();
}

void Controller::openAdmin()
{
    if(isAdmin){
        loadUsersinView();
        admin->show();
    }
    else{
        admin = new Admin(this,view);
        loadUsersinView();
        view->changeTitleAdmin(QString("Aggiorna admin"));
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

}

void Controller::annullaUtente()
{
    qDebug() << "test";
}

void Controller::setView(MainWindow *v)
{
  view = v;
}

void Controller::salvaUtente()
{
  if(pathJsonUsers == ""){
      pathJsonUsers = QFileDialog::getOpenFileName(view, tr("Carica json Utenti"), "/home/student/QTheater/json", tr("json(*.json)"),nullptr,QFileDialog::DontUseNativeDialog);
    }
  QFile file(pathJsonUsers);
      if( !file.open( QIODevice::ReadOnly ) )
      {
          openError(QString("File open error: Read"));
      }

      QJsonDocument jsonOrg = QJsonDocument::fromJson( file.readAll() );
      file.close();

      QJsonValue v = jsonOrg.object().value(QString("Utenti"));

      QJsonArray array = v.toArray();

      QJsonObject newUser;
      newUser.insert("name", utente->getName());
      newUser.insert("surname", utente->getSurname());
      newUser.insert("CF", utente->getCF());
      newUser.insert("age", utente->getAge());
      newUser.insert("tel.Num", utente->getNumTel());

      array.push_back(newUser);

      QJsonObject obj;
      obj.insert("Utenti",array);

      QJsonDocument doc(obj);

      if( !file.open( QIODevice::WriteOnly ) )
      {
          openError(QString("File open error: Write"));
      }

      file.write(doc.toJson());
      file.close();
}

void Controller::readUtenti()
{

  pathJsonUsers = QFileDialog::getOpenFileName(view, tr("Carica json Utenti"), "/home/student/QTheater/json", tr("json(*.json)"),nullptr,QFileDialog::DontUseNativeDialog);
  QFile file(pathJsonUsers);

  if (!file.open(QIODevice::ReadOnly)) {
        openError(QString("File open error: Read"));
  } else {

    model->clearVectorUtenti();

      QString json = file.readAll();

      QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));
      if(!doc.isEmpty()){
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

          view->changeTitleChooseUtenti("Cambia file json per utenti");
        }else{
          openError(QString("Empty file"));
        }

    }


}

void Controller::readFimiglie()
{

}

void Controller::readEntrata()
{

}


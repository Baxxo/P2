#include "controller.h"

#include <QFileDialog>
#include <QTimer>

using std::string;

Controller::Controller(QObject * parent, Model * m):
  QObject(parent), model(m),
  isAdminOpen(false),
  isClientOpen(false),
  isUtenteOpen(false),
  isFamigliaOpen(false),
  pathJsonUsers(""),
  pathJsonFamiglie(""),
  pathJsonEntrata(""),
  fam(nullptr){}

bool Controller::getIsAdmin() const {
  return isAdminOpen;
}

void Controller::setIsAdmin(bool value) {
  isAdminOpen = value;
  if (isAdminOpen) {
    view -> changeTitleAdmin(QString("Aggiorna admin"));
  } else {
    view -> changeTitleAdmin(QString("Admin"));
  }
}

QString Controller::getPathJsonUsers() const {
  return pathJsonUsers;
}

QString Controller::getPathJsonFamiglie() const {
  return pathJsonFamiglie;
}

QString Controller::getPathJsonEntrata() const {
  return pathJsonEntrata;
}

void Controller::openError(QString message) {
  if (err) {
    err -> setMessage(message);
  } else {
    err = new ErrorDisplay(nullptr, message);
  }
  err -> show();
}

void Controller::createFamiglia(Famiglia &f, Utente *u)
{
  model->addUserToFamily(f,u);
}

Famiglia *Controller::getFam() const
{
  return fam;
}

bool Controller::addUserToFamily(const QString& cf)
{
  Utente * u = model->getUtente(cf.toUtf8().constData());
  if(fam!= nullptr && u != nullptr){
      fam->addMembro(u);
      return true;
    }
  return false;
}

bool Controller::removeUserFromFamily(const QString &cf)
{
  Utente * u = model->getUtente(cf.toUtf8().constData());
  if(fam!= nullptr && u != nullptr){
      fam->removeMembro(u);
      return true;
    }
  return false;
}

void Controller::openAdmin() {
  if (!isAdminOpen || !admin) {
    admin = new Admin(this, view);
    isAdminOpen = true;
  }
  view -> changeTitleAdmin(QString("Aggiorna admin"));
  loadUsersinView();
  admin -> show();

}

void Controller::openClient() {
  if (!isClientOpen || !client) {
      client = new Client(this);
  }
  client -> show();
  isClientOpen = true;

}

void Controller::openUtente() {
  if (!isUtenteOpen || !utente) {
      utente = new Utente_View(this);
  }
  utente -> show();
  isUtenteOpen = true;
}

void Controller::openFamiglia() {
  if (!isFamigliaOpen || !famigliaView) {
      fam = new Famiglia();
      famigliaView = new Famiglia_View(this);
  }
  if(model->getListUtenti().isEmpty()){
      QFile file;
      QVariantList* list = readUtenti(file);

      if(model->getListUtenti().isEmpty() && list != nullptr){
          popolaVectorUtenti(*list);
        }

      view -> changeTitleChooseUtenti("Cambia file json per utenti");
  }

  famigliaView->clearList();
  for (auto it = model -> getListUtenti().cbegin(); it != model -> getListUtenti().cend(); ++it) {
      QString text = QString::fromStdString(((*it) -> getSurname() + " " + (*it) -> getName()+ " ( " + (*it) -> getCodFisc() + " )").c_str());
      QString cf = QString::fromStdString(((*it)->getCodFisc()).c_str());
      famigliaView->addUtenteToLista(text,cf);
  }

  isFamigliaOpen = true;  

  QTimer::singleShot(0,famigliaView,SLOT(resizeMe()));
  famigliaView -> show();

}

void Controller::searchCF() {
    string cf = famigliaView->getCF_SearchText().toUtf8().constData();
    if(cf != "" && cf != "Type in a CF and press search"){
        if(!fam->hasMembro(new Utente(cf))){
            bool find =  model->searchCf(cf);
            if(find){
                famigliaView->findUser(famigliaView->getCF_SearchText());
              }else{
                err = new ErrorDisplay(nullptr,"Utente non trovato");
                err->show();
                famigliaView->setUtilityText(QString("Utente non trovato"));
              }
          }else{
            err = new ErrorDisplay(nullptr,"Codice fiscale gia' presente nella famiglia");
            err->show();
          }
      }else{
        err = new ErrorDisplay(nullptr,"Inserisci un codice fiscale valido");
        err->show();
      }
}

void Controller::annullaUtente() {
}

void Controller::setView(MainWindow * v) {
  view = v;
}

void Controller::salvaUtente() {
  if (pathJsonUsers == "") {
    pathJsonUsers = QFileDialog::getOpenFileName(view, tr("Carica json Utenti"), "/home/student/QTheater/json", tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }
  QFile file(pathJsonUsers);
  if (!file.open(QIODevice::ReadOnly)) {
    openError(QString("File open error: Read"));
  }

  QJsonDocument jsonOrg = QJsonDocument::fromJson(file.readAll());
  file.close();

  QJsonValue v = jsonOrg.object().value(QString("Utenti"));

  QJsonArray array = v.toArray();

  QJsonObject newUser;
  newUser.insert("CF", utente -> getCF());
  newUser.insert("name", utente -> getName());
  newUser.insert("surname", utente -> getSurname());
  newUser.insert("age", utente -> getAge());
  newUser.insert("tel.Num", utente -> getNumTel());

  array.push_back(newUser);

  QJsonObject obj;
  obj.insert("Utenti", array);

  QJsonDocument doc(obj);

  if (!file.open(QIODevice::WriteOnly)) {
    openError(QString("File open error: Write"));
  }

  file.write(doc.toJson());
  file.close();

  famigliaView->setUtilityText("Famiglia Salvata e registrata");
}

void Controller::salvaFamiglia() {

  fam->setName(famigliaView->getFamilyName().toStdString());
  model->addFamiglia(*fam);

  if (pathJsonFamiglie == "") {
    pathJsonFamiglie = QFileDialog::getOpenFileName(view, tr("Scegli json famiglie"), "/home/student/QTheater/json", tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }
  QFile file(pathJsonFamiglie);
  if (!file.open(QIODevice::ReadOnly)) {
    openError(QString("File open error: Read"));
  }

  QJsonDocument jsonOrg = QJsonDocument::fromJson(file.readAll());
  file.close();

  QJsonValue v = jsonOrg.object().value(QString("Famiglie"));

  QJsonArray array = v.toArray();

  QJsonObject newFamily;
  newFamily.insert("Name",famigliaView->getFamilyName());
  for(unsigned int i=0;i<fam->getSize();i++){
      newFamily.insert(QString::fromStdString("Utente"+std::to_string(i+1)), QString::fromStdString(((*fam)[i])->getCodFisc()));
    }

  array.push_back(newFamily);

  QJsonObject obj;
  obj.insert("Famiglie", array);

  QJsonDocument doc(obj);

  if (!file.open(QIODevice::WriteOnly)) {
    openError(QString("File open error: Write"));
  }

  file.write(doc.toJson());
  file.close();


}

void Controller::loadUsersinView() {

    QFile file;
    QVariantList* list = readUtenti(file);
    if(list != nullptr){

        if(model->getListUtenti().isEmpty()){
            popolaVectorUtenti(*list);
          }

        view -> changeTitleChooseUtenti("Cambia file json per utenti");
        QFileInfo info(file.fileName());
        view -> setLabelPathUser(info.fileName());

        if(!admin || !isAdminOpen){
            admin = new Admin(this, view);
            isAdminOpen = true;
        }
        admin -> clearListUtenti();
        Utente* u;
        for (auto it = model -> getListUtenti().cbegin(); it != model -> getListUtenti().cend(); ++it) {
            u = new Utente(**it);
            string s = u->getSurname() + " " + u->getName() + " ( " + u->getCodFisc() + " )";
            admin -> addUtente(QString(s.c_str()));
        }

        if(u) delete u;
      }
}

void Controller::loadFamiliesinView()
{
  QFile file;
  QVariantList* list = readFimiglie(file);
  if(list != nullptr){

      if(model->getListFamiglie().isEmpty()){
          popolaVectorFamiglie(*list);
        }


      view -> changeTitleChooseFamiglie("Cambia file json per Famiglie");
      QFileInfo info(file.fileName());
      view -> setLabelPathFamiglie(info.fileName());

      if(!admin || !isAdminOpen){
          admin = new Admin(this, view);
          isAdminOpen = true;
      }
      admin -> clearListFamiglie();
      for (auto it = model -> getListFamiglie().cbegin(); it != model -> getListFamiglie().cend(); ++it) {
          qDebug() << "controller ciclo famiglie";
          admin -> addFamiglia(QString::fromStdString((*it)->getName() + " (membri: " + std::to_string((*it)->getSize()) + " )"));
      }
    }
}

void Controller::loadEntrateinView()
{

}

QVariantList* Controller::readUtenti(QFile &file, bool update) {

  if (pathJsonUsers == "" || update) {
    pathJsonUsers = QFileDialog::getOpenFileName(view, tr("Carica json Utenti"), "/home/student/QTheater/json", tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }
  file.setFileName(pathJsonUsers);

  if (!file.open(QIODevice::ReadOnly)) {
    openError(QString("File open error: Read"));
  } else {

    model -> clearVectorUtenti();

    QString json = file.readAll();

    QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));
    if (!doc.isEmpty()) {
      QJsonObject jObj = doc.object();

      QVariantMap mainMap = jObj.toVariantMap();
      QVariantList* localList = new QVariantList();
      *localList = mainMap["Utenti"].toList();

      return localList;
    } else {
      openError(QString("Empty file"));
    }

  }

  return nullptr;

}

QVariantList *Controller::readFimiglie(QFile &file, bool update)
{

  if (pathJsonFamiglie == "" || update) {
    pathJsonFamiglie = QFileDialog::getOpenFileName(view, tr("Carica json Famiglie"), "/home/student/QTheater/json", tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }
  file.setFileName(pathJsonFamiglie);

  if (!file.open(QIODevice::ReadOnly)) {
    openError(QString("File open error: Read"));
  } else {

    model -> clearVectorFamiglie();

    QString json = file.readAll();

    QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));
    if (!doc.isEmpty()) {
      QJsonObject jObj = doc.object();

      QVariantMap mainMap = jObj.toVariantMap();
      QVariantList* localList = new QVariantList();
      *localList = mainMap["Famiglie"].toList();

      return localList;
    } else {
      openError(QString("Empty file"));
    }

  }

  return nullptr;

}

QVariantList *Controller::readEntrata(QFile &file, bool update)
{

}

void Controller::popolaVectorUtenti(const QVariantList &list)
{
    Utente *u;

    for (int i = 0; i < list.length(); ++i) {
      QVariantMap map = list[i].toMap();
      string cf = map["CF"].toString().toUtf8().constData();
      if(!model->searchCf(cf)){
          u = new Utente(
              map["CF"].toString().toUtf8().constData(),
              map["name"].toString().toUtf8().constData(),
              map["surname"].toString().toUtf8().constData(),
              map["age"].toInt(),
              map["tel.Num"].toString().toUtf8().constData()
            );
          model -> addUtente(*u);
        }
    }

}

void Controller::popolaVectorFamiglie(const QVariantList &list)
{
  Famiglia *fam;

  for (int i = 0; i < list.length(); ++i) {
    QVariantMap map = list[i].toMap();

    string name = map["Name"].toString().toUtf8().constData();

    if(!model->searchNameFamiglia(name)){
        fam = new Famiglia(name);
        for(unsigned int j=1;j<map.size();j++){
            QString key = QString::fromStdString("Utente"+std::to_string(j));
            string cf = map[key].toString().toUtf8().constData();
            Utente* u = model->getUtente(cf);
            fam->addMembro(u);
          }
        model->addFamiglia(*fam);
      }
  }
}

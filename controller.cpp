#include "controller.h"

#include <QFileDialog>

using std::string;

Controller::Controller(QObject * parent, Model * m):
  QObject(parent), model(m), isAdminOpen(false), isBigliettoOpen(false), isClientOpen(false), isUtenteOpen(false), isFamigliaOpen(false), pathJsonUsers(""), pathjsonPosti(""), pathJsonFilm("") {}

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

QString Controller::getPathJsonPosti() const
{
    return pathjsonPosti;
}

QString Controller::getPathJsonFilm() const
{
    return pathJsonFilm;
}

void Controller::openError(QString message) {
  if (err) {
    err -> setMessage(message);
  } else {
    err = new ErrorDisplay(nullptr, message);
  }
  err -> show();
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
      famigliaView = new Famiglia_View(this);
  }


  if(model->getListUtenti().isEmpty()){
      QFile file;
      QVariantList* list = readUtenti(file);
      if(list != nullptr){
          popolaVectorUtenti(*list);
      }
  }

  famigliaView->clearList();
  for (auto it = model -> getListUtenti().cbegin(); it != model -> getListUtenti().cend(); ++it) {
      QString text = QString::fromUtf8(((*it) -> getSurname() + " " + (*it) -> getName()+ " ( " + (*it) -> getCodFisc() + " )").c_str());
      QString cf = QString::fromUtf8(((*it)->getCodFisc()).c_str());
      famigliaView->addUtenteToLista(text,cf);
  }

  isFamigliaOpen = true;
  famigliaView -> show();
}

void Controller::listaUtenti() {
  /*
  QJsonObject::iterator a= objUtenti->begin();
  for(int i=0; i<objUtenti->size();i++){
      menu->addItem(a.key());
      a++;
  }
  */
  //readUtenti();

  QString key;
  bool found = false;

  /*for (auto it = model->getListUtenti().cbegin(); it != model->getListUtenti().cend(); ++it) {
      if(it.key()==famiglia->getSearch()){
          key= a.key();
          found=true;
      }
  }*/

  if (!found) {
    key = "CF non presente, crea nuovo utente";
  }

  //famigliaView -> addUtenteToLista(key);

}

void Controller::openBiglietto()
{
    if(!isBigliettoOpen || !bigliettoView){
        bigliettoView= new Biglietto_View(this);
    }

    isBigliettoOpen=true;
    bigliettoView->show();
}

void Controller::annullaUtente() {
  qDebug() << "test";
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
  newUser.insert("name", utente -> getName());
  newUser.insert("surname", utente -> getSurname());
  newUser.insert("CF", utente -> getCF());
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
}

void Controller::salvaFamiglia() {
  if (pathJsonFamiglie == "") {
    pathJsonFamiglie = QFileDialog::getOpenFileName(view, tr("Carica json Utenti"), "/home/student/QTheater/json", tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }
  QFile file(pathJsonUsers);
  if (!file.open(QIODevice::ReadOnly)) {
    openError(QString("File open error: Read"));
  }

  QJsonDocument jsonOrg = QJsonDocument::fromJson(file.readAll());
  file.close();

  QJsonObject newUser;
  for (int i = 0; i < famigliaView -> getListSize(); i++) {
    newUser.insert(famigliaView -> getItem(i), famigliaView -> getItem(i));
  }

  qDebug() << newUser.length() << famigliaView -> getListSize();
  QJsonObject fam;
  fam.insert(famigliaView -> getFamilyName(), newUser);

  QJsonDocument doc(fam);

  if (!file.open(QIODevice::WriteOnly)) {
    openError(QString("File open error: Write"));
  }

  file.write(doc.toJson());
  file.close();
}

void Controller::stpBigl()
{
    if(bigliettoView->getTipologia()=="singolo"){
        QString utente=bigliettoView->getSearch();
        QString CFUtente= QString::fromStdString(model->getUtente(utente.toStdString())->getCodFisc());

    //save acquirente per tracciamento
        QFile storico("path");
        if (!storico.open(QIODevice::ReadWrite)) {
            openError(QString("File open error: Read"));
        }
        else{
            //read from existing file and load existing users on local obj

            QJsonObject obj;
            QString settings;
            QJsonDocument doc(QJsonDocument::fromJson(settings.toUtf8()));
            settings= storico.readAll();
            obj=doc.object();

            //save utente in json
            obj.insert(CFUtente, "nome sala");
            doc.setObject(obj);
            storico.write(doc.toJson());
        }
        storico.close();

      //save nuovo posto in sala x
        QFile file("path");
        if (!file.open(QIODevice::WriteOnly)) {
            openError(QString("File open error: Read"));
        }
        else{

            //load dei posti già fatto in un'altra funzione perchè servirà prima
            //save posto nuovo
            /*questi QJsonObj saranno dichiarati private e non dichiarati localmente così visto che il load è esterno alla funzione*/
            QJsonObject posti;
            posti.insert("nome Sala", "ci sarà un getter di colonna*riga");
        }

    if(bigliettoView->getTipologia()=="abbonamento"){
        qDebug() << "abbonamento";
    }



    }
}

void Controller::showSala()
{
    //QTableWidget sala(2, 3);
    bigliettoView->getSalaView();

}


void Controller::loadUsersinView() {

    QFile file;
    QVariantList* list = readUtenti(file);
    if(list != nullptr){

        popolaVectorUtenti(*list);

        view -> changeTitleChooseUtenti("Cambia file json per utenti");
        QFileInfo info(file.fileName());
        view -> setLabelPathUser(info.fileName());

        if(!admin || !isAdminOpen){
            admin = new Admin(this, view);
            isAdminOpen = true;
        }
        admin -> clearListUtenti();
        for (auto it = model -> getListUtenti().cbegin(); it != model -> getListUtenti().cend(); ++it) {
            admin -> addUtente(QString::fromUtf8((( * it) -> getSurname() + " " + ( * it) -> getName()).c_str()));
        }
    }
}

void Controller::loadPostiOccupati()
{
    QFile file;
    QVariantList* list= readPosti(file);
    if (list !=nullptr) {
        qDebug()<< "cose";
    }

}

void Controller::loadFilm()
{
    QFile file;
    QVariantList* list= readFilm(file);
    if (list !=nullptr) {
        qDebug()<< "cose";
    }
}

QVariantList* Controller::readUtenti(QFile &file) {

  if (pathJsonUsers == "") {
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

QVariantList *Controller::readPosti(QFile &file)
{
    if (pathjsonPosti == "") {
      pathjsonPosti = QFileDialog::getOpenFileName(view, tr("Carica json Posti"), "/home/student/QTheater/json", tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
    }
    file.setFileName(pathjsonPosti);

    if (!file.open(QIODevice::ReadOnly)) {
      openError(QString("File open error: Read"));
    } else {

        qDebug() << "ciao:)";
      //model -> clearVectorUtenti();

      QString json = file.readAll();

      QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));
      if (!doc.isEmpty()) {
        QJsonObject jObj = doc.object();

        QVariantMap mainMap = jObj.toVariantMap();
        QVariantList* localList = new QVariantList();
        *localList = mainMap["Posti"].toList();

        return localList;
      } else {
        openError(QString("Empty file"));
      }

    }

    return nullptr;
}

QVariantList *Controller::readFilm(QFile &file)
{
    if (pathJsonFilm == "") {
      pathJsonFilm = QFileDialog::getOpenFileName(view, tr("Carica json Posti"), "/home/student/QTheater/json", tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
    }
    file.setFileName(pathJsonFilm);

    if (!file.open(QIODevice::ReadOnly)) {
      openError(QString("File open error: Read"));
    } else {

        qDebug() << "ciao:)";
      //model -> clearVectorUtenti();

      QString json = file.readAll();

      QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));
      if (!doc.isEmpty()) {
        QJsonObject jObj = doc.object();

        QVariantMap mainMap = jObj.toVariantMap();
        QVariantList* localList = new QVariantList();
        *localList = mainMap["Film"].toList();

        return localList;
      } else {
        openError(QString("Empty file"));
      }

    }

    return nullptr;
}

void Controller::popolaVectorUtenti(const QVariantList &list)
{
    Utente *u;
    for (int i = 0; i < list.length(); ++i) {
      QVariantMap map = list[i].toMap();
      u = new Utente(map["name"].toString().toUtf8().constData(),
        map["surname"].toString().toUtf8().constData(),
        map["age"].toInt(),
        map["CF"].toString().toUtf8().constData(),
        map["tel.Num"].toString().toUtf8().constData());
      model -> addUtente(*u);
    }

}

void Controller::popolaVectorPosti(const QVariantList &list)
{
    Utente *u;
    for (int i = 0; i < list.length(); ++i) {
      QVariantMap map = list[i].toMap();
      u = new Utente(map["name"].toString().toUtf8().constData(),
        map["surname"].toString().toUtf8().constData(),
        map["age"].toInt(),
        map["CF"].toString().toUtf8().constData(),
        map["tel.Num"].toString().toUtf8().constData());
      model -> addAcquisto(*u);
    }
}

void Controller::readFimiglie() {

}

void Controller::readEntrata() {

}

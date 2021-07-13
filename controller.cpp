#include "controller.h"

#include <QDate>
#include <QFileDialog>
#include <QTimer>

#include <QDebug>

using std::string;

Controller::Controller(QObject *parent, Model *m)
    : QObject(parent),
      model(m),
      view(nullptr),
      admin(nullptr),
      client(nullptr),
      utente(nullptr),
      famigliaView(nullptr),
      abbonamentoView(nullptr),
      bigliettoView(nullptr),
      pathJsonUsers(""),
      pathJsonFamiglie(""),
      pathJsonEntrata(""),
      pathJsonPosti(""),
      pathJsonFilm(""),
      pathJsonSale(""),
      objUtenti(nullptr),
      fam(nullptr),
      abb(nullptr),
      codAbb(0),
      abbFam(nullptr),
      codAbbFam(0),
      codBigl(0),
      err(nullptr) {}

QString Controller::getPathJsonUsers() const { return pathJsonUsers; }

QString Controller::getPathJsonFamiglie() const { return pathJsonFamiglie; }

QString Controller::getPathJsonEntrata() const { return pathJsonEntrata; }

QString Controller::getPathJsonPosti() const { return pathJsonPosti; }

QString Controller::getPathJsonSale() const { return pathJsonSale; }

QString Controller::getPathJsonFilm() const { return pathJsonFilm; }

bool Controller::removeAbbonamento(const QString &cod) {
  if (model->searchEntrata(cod.toStdString())) {
    return model->removeEntrata(EntrataFilm(cod.toStdString()));
  }
  return false;
}

void Controller::setView(MainWindow *v) { view = v; }

void Controller::openError(const QString &message) {
  if (err) {
    err->setMessage(message);
  } else {
    err = new ErrorDisplay(nullptr, message);
  }
  err->show();
}

void Controller::createFamiglia(Famiglia &f, Utente *u) {
  model->addUserToFamily(f, u);
}

Famiglia *Controller::getFam() const { return fam; }

bool Controller::addUserToFamily(const QString &cf) {
  Utente *u = model->getUtente(cf.toStdString());
  if (fam != nullptr && u != nullptr) {
    fam->addMembro(u);
    return true;
  }
  return false;
}

bool Controller::removeUserFromFamily(const QString &cf) {
  Utente *u = model->getUtente(cf.toStdString());
  if (fam != nullptr && u != nullptr) {
    fam->removeMembro(u);
    return true;
  }
  return false;
}

bool Controller::createAbbonamento(const QString &cf) {
  bool chk = true;
  if (abb) {
    delete abb;
    abb = nullptr;
  }
  QDate date = date.currentDate();
  QString year = date.toString("yyyy");
  QString month = date.toString("MM");
  QString day = date.toString("dd");

  if (model->searchCf(cf.toStdString())) {
    abb = new Abbonamento(new Data(year.toUInt(), month.toUInt(), day.toUInt()),
                          cf.toStdString(), 7.5, std::to_string(codAbb++), 10);

    model->addEntrata(abb);

    QFile file(pathJsonEntrata);
    if (!file.open(QIODevice::ReadOnly)) {
      openError(QString("File open error: Read"));
    }

    QJsonDocument jsonOrg = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonValue v = jsonOrg.object().value(QString("Entrate"));

    QJsonArray array = v.toArray();

    QJsonObject newAbbonamento;
    newAbbonamento.insert("Tipo", "Abbonamento");
    newAbbonamento.insert("Data",
                          QString::fromStdString(abb->getData()->ToString()));
    newAbbonamento.insert("Utente", QString::fromStdString(abb->getUtente()));
    newAbbonamento.insert("Codice", QString::fromStdString(abb->getCodice()));
    newAbbonamento.insert("Entrate_rimaste", abb->getEntrate());

    array.push_back(newAbbonamento);

    QJsonObject obj;
    obj.insert("Entrate", array);

    QJsonDocument doc(obj);

    if (!file.open(QIODevice::WriteOnly)) {
      openError(QString("File open error: Write"));
    }

    file.write(doc.toJson());
    file.close();
  }

  return chk;
}

bool Controller::createAbbonamentoFamigliare(const QString &name,
                                             const QString &cf) {
  bool chk = true;
  if (abbFam) {
    delete abbFam;
    abbFam = nullptr;
  }

  QDate date = date.currentDate();
  QString year = date.toString("yyyy");
  QString month = date.toString("MM");
  QString day = date.toString("dd");

  if (model->searchCf(cf.toStdString())) {
    if (model->searchNameFamiglia(name.toStdString())) {
      abbFam = new AbbonamentoFamigliare(
          new Data(year.toUInt(), month.toUInt(), day.toUInt()),
          cf.toStdString(), name.toStdString(), 7.5,
          std::to_string(codAbbFam++), 10);

      model->addEntrata(abbFam);

      QFile file(pathJsonEntrata);
      if (!file.open(QIODevice::ReadOnly)) {
        openError(QString("File open error: Read"));
      }

      QJsonDocument jsonOrg = QJsonDocument::fromJson(file.readAll());
      file.close();

      QJsonValue v = jsonOrg.object().value(QString("Entrate"));

      QJsonArray array = v.toArray();

      QJsonObject newAbbonamento;
      newAbbonamento.insert("Tipo", "Abbonamento_Famigliare");
      newAbbonamento.insert(
          "Data", QString::fromStdString(abbFam->getData()->ToString()));
      newAbbonamento.insert("Utente",
                            QString::fromStdString(abbFam->getUtente()));
      newAbbonamento.insert("Famiglia",
                            QString::fromStdString(abbFam->getFamiglia()));
      newAbbonamento.insert("Codice",
                            QString::fromStdString(abbFam->getCodice()));
      newAbbonamento.insert("Entrate_rimaste", abbFam->getEntrate());

      array.push_back(newAbbonamento);

      QJsonObject obj;
      obj.insert("Entrate", array);

      QJsonDocument doc(obj);

      if (!file.open(QIODevice::WriteOnly)) {
        openError(QString("File open error: Write"));
      }

      file.write(doc.toJson());
      file.close();
    }
  }

  return chk;
}

void Controller::loadUtentiInAdmin() {
  admin->clearListUtenti();
  for (auto it = model->getListUtenti().cbegin();
       it != model->getListUtenti().cend(); ++it) {
    string s = (**it).getSurname() + " " + (**it).getName() + " ( " +
               (**it).getCodFisc() + " )";
    admin->addUtente(QString(s.c_str()));
  }
}

void Controller::loadFamiglieInAdmin() {
  admin->clearListFamiglie();
  for (auto it = model->getListFamiglie().cbegin();
       it != model->getListFamiglie().cend(); ++it) {
    admin->addFamiglia(QString::fromStdString(
        (*it)->getName() + " (membri: " + std::to_string((*it)->getSize()) +
        " )"));
  }
}

void Controller::loadEntrateInAdmin() {
  admin->clearListEntrate();
  for (auto it = model->getListEntrate().cbegin();
       it != model->getListEntrate().cend(); ++it) {
    Abbonamento *ab = dynamic_cast<Abbonamento *>(&(**it));

    AbbonamentoFamigliare *abf = dynamic_cast<AbbonamentoFamigliare *>(ab);
    if (abf) {
      admin->addEntrata("Abbonamento Famigliare " +
                            QString::fromStdString(abf->getFamiglia()),
                        QString::fromStdString(abf->getCodice()));
    } else {
      Utente *u_tmp = model->getUtente(ab->getUtente());
      string s1 = "Abbonamento " + u_tmp->toString();
      string s2 = ab->getCodice();
      admin->addEntrata(QString::fromStdString(s1), QString::fromStdString(s2));
    }
  }
}

void Controller::openAdmin() {
  if (admin == nullptr) {
    admin = new Admin(this, view);
  }
  view->changeTitleAdmin(QString("Aggiorna admin"));

  if (pathJsonUsers == "") loadUsers();

  loadUtentiInAdmin();

  if (pathJsonFamiglie == "") loadFamilies();

  loadFamiglieInAdmin();

  if (pathJsonEntrata == "") loadEntrate();

  loadEntrateInAdmin();

  admin->show();
}

void Controller::openClient() {
  if (!client) {
    client = new Client(this);
  }

  if (pathJsonUsers == "") loadUsers();
  if (pathJsonFamiglie == "") loadFamilies();
  if (pathJsonEntrata == "") loadEntrate();

  client->show();
}

void Controller::openUtente() {
  if (!utente) {
    utente = new Utente_View(this);
  }
  utente->show();
}

void Controller::openFamiglia() {
  if (!famigliaView) {
    fam = new Famiglia();
    famigliaView = new Famiglia_View(this);
  }

  if (pathJsonUsers == "") loadUsers();
  if (pathJsonFamiglie == "") loadFamilies();

  famigliaView->clearList();
  for (auto it = model->getListUtenti().cbegin();
       it != model->getListUtenti().cend(); ++it) {
    QString text =
        QString::fromStdString(((*it)->getSurname() + " " + (*it)->getName() +
                                " ( " + (*it)->getCodFisc() + " )")
                                   .c_str());
    QString cf = QString::fromStdString(((*it)->getCodFisc()).c_str());
    famigliaView->addUtenteToLista(text, cf);
  }

  QTimer::singleShot(0, famigliaView, SLOT(resizeMe()));
  famigliaView->show();
}

void Controller::openAbbonamento() {
  if (!abbonamentoView) {
    abbonamentoView = new Abbonamento_view(this);
  }

  if (pathJsonUsers == "") loadUsers();

  abbonamentoView->clearListUtenti();
  for (auto it = model->getListUtenti().cbegin();
       it != model->getListUtenti().cend(); ++it) {
    abbonamentoView->addUtente(
        QString::fromStdString((*it)->getSurname() + " " + (*it)->getName() +
                               " ( " + (*it)->getCodFisc() + " )"),
        QString::fromStdString((*it)->getCodFisc()));
  }

  if (pathJsonFamiglie == "") loadFamilies();

  abbonamentoView->clearListFamiglie();

  for (auto it = model->getListFamiglie().cbegin();
       it != model->getListFamiglie().cend(); ++it) {
    abbonamentoView->addFamiglia(
        QString::fromStdString((*it)->getName() + " (membri: " +
                               std::to_string((*it)->getSize()) + " )"),
        QString::fromStdString((*it)->getName()));
  }

  QTimer::singleShot(0, abbonamentoView, SLOT(resizeMe()));

  abbonamentoView->show();
}

void Controller::openBiglietto() {
  if (!bigliettoView) {
    bigliettoView = new Biglietto_View(this);
  }

  if (pathJsonUsers == "") loadUsers();
  if (pathJsonFamiglie == "") loadFamilies();

  QTimer::singleShot(0, bigliettoView, SLOT(resizeMe()));

  bigliettoView->show();
}

void Controller::searchCF() {
  string cf = famigliaView->getCF_SearchText().toStdString();
  if (cf != "" && cf != "Type in a CF and press search") {
    if (!fam->hasMembro(new Utente(cf))) {
      bool find = model->searchCf(cf);
      if (find) {
        famigliaView->findUser(famigliaView->getCF_SearchText());
      } else {
        openError("Utente non trovato");
        famigliaView->setUtilityText(QString("Utente non trovato"));
      }
    } else {
      openError("Codice fiscale gia' presente nella famiglia");
    }
  } else {
    openError("Inserisci un codice fiscale valido");
  }
}

void Controller::loadUsersSlot() { loadUsers(true); }

void Controller::loadFamiliesSlot() { loadFamilies(true); }

void Controller::loadEntrateSlot() { loadEntrate(true); }

void Controller::loadPostiSlot() { loadPostiOccupati(true); }

void Controller::loadSaleSlot() { loadSale(true); }

void Controller::loadFilmSlot() { loadFilm(true); }

void Controller::annullaUtente() { qDebug() << "test"; }

void Controller::salvaUtente() {
  if (pathJsonUsers == "") {
    pathJsonUsers = QFileDialog::getOpenFileName(
        view, tr("Carica json Utenti"), "/home/student/QTheater/json",
        tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }
  if (!model->searchCf(utente->getCF().toStdString())) {
    Utente *u = new Utente(
        utente->getCF().toStdString(), utente->getName().toStdString(),
        utente->getSurname().toStdString(), utente->getAge().toUInt(),
        utente->getNumTel().toStdString());
    model->addUtente(u);

    QFile file(pathJsonUsers);
    if (!file.open(QIODevice::ReadOnly)) {
      openError(QString("File open error: Read"));
    }

    QJsonDocument jsonOrg = QJsonDocument::fromJson(file.readAll());
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
    obj.insert("Utenti", array);

    QJsonDocument doc(obj);

    if (!file.open(QIODevice::WriteOnly)) {
      openError(QString("File open error: Write"));
    }

    file.write(doc.toJson());
    file.close();
    utente->setConferma("Utente inserito");
    if (admin && admin->isVisible()) {
      loadUtentiInAdmin();
    }
  } else {
    utente->setConferma(("Utente gia` presente nel programma"));
    openError("Utente gia` presente nel programma");
  }
}

void Controller::salvaFamiglia() {
  if (!model->searchNameFamiglia(famigliaView->getFamilyName().toStdString())) {
    QString name = famigliaView->getFamilyName();
    if (name != "Type in a family name" && name != "") {
      fam->setName(name.toStdString());
      if (!fam->isEmpty()) {
        model->addFamiglia(fam);

        if (pathJsonFamiglie == "") {
          pathJsonFamiglie = QFileDialog::getOpenFileName(
              view, tr("Scegli json famiglie"), "/home/student/QTheater/json",
              tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
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
        newFamily.insert("Name", famigliaView->getFamilyName());
        for (unsigned int i = 0; i < fam->getSize(); i++) {
          newFamily.insert(
              QString::fromStdString("Utente" + std::to_string(i + 1)),
              QString::fromStdString(((*fam)[i])->getCodFisc()));
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

        famigliaView->setUtilityText("Famiglia Salvata e registrata");
        if (admin && admin->isVisible()) {
          loadFamiglieInAdmin();
        }
      } else {
        openError("inserisci almeno un membro");
      }
    } else {
      openError("inserisci nome famiglia");
    }
  }
}

void Controller::newFilm() {
  QFile file(pathJsonFilm);
  if (!file.open(QIODevice::ReadWrite)) {
    openError(QString("File open error: Read"));
  }

  QJsonDocument doc;

  filmObj.insert(admin->getNomeFilm(), admin->getSalaFilm());

  doc.setObject(filmObj);
  file.write(doc.toJson());
  file.close();
}

void Controller::newSala() {
  if (pathJsonSale == "") {
    pathJsonSale = QFileDialog::getOpenFileName(
        view, tr("Carica json Sale"), "/home/student/QTheater/json",
        tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }
  QFile file(pathJsonSale);
  if (!file.open(QIODevice::ReadOnly)) {
    openError(QString("File open error: Read"));
  }

  QJsonDocument jsonOrg = QJsonDocument::fromJson(file.readAll());
  file.close();

  QJsonValue v = jsonOrg.object().value(QString("Sale"));

  QJsonArray array = v.toArray();

  QJsonObject newSala;
  newSala.insert("righe", admin->getRigheSala());
  newSala.insert("colonne", admin->getColonneSala());
  newSala.insert("nome_sala", admin->getNomeSala());

  array.push_back(newSala);

  QJsonObject obj;
  obj.insert("Sale", array);

  QJsonDocument doc(obj);

  if (!file.open(QIODevice::WriteOnly)) {
    openError(QString("File open error: Write"));
  }

  file.write(doc.toJson());
  file.close();
}

void Controller::stpBigl() {
  if (bigliettoView->getTipologia() == "Singolo") {
    QString utente = bigliettoView->getSearch();
    if (model->searchCf(utente.toStdString())) {
      bigliettoView->setUtilitySearchText(QString("Codice fiscale Trovato"));

      // save acquirente per tracciamento
      QFile storico("path");
      if (!storico.open(QIODevice::ReadWrite)) {
        openError(QString("File open error: Read"));
      } else {
        // read from existing file and load existing users on local obj

        QJsonObject obj;
        QString settings;
        QJsonDocument doc(QJsonDocument::fromJson(settings.toUtf8()));
        settings = storico.readAll();
        obj = doc.object();

        // save utente in json
        obj.insert(utente, "nome sala");
        doc.setObject(obj);
        storico.write(doc.toJson());
      }
      storico.close();

      // save nuovo posto in sala x
      QFile file("path");
      if (!file.open(QIODevice::WriteOnly)) {
        openError(QString("File open error: Read"));
      } else {
        // load dei posti già fatto in un'altra funzione perchè servirà prima
        // save posto nuovo
        /*questi QJsonObj saranno dichiarati private e non dichiarati
         * localmente così visto che il load è esterno alla funzione*/
        QJsonObject posti;
        posti.insert("nome Sala", "ci sarà un getter di colonna*riga");
      }
    } else {
      bigliettoView->setUtilitySearchText(
          QString("Codice fiscale non trovato"));
      openError(QString("Codice fiscale non trovato"));
    }
  } else if (bigliettoView->getTipologia() == "Abbonamento") {
    qDebug() << "abbonamento";
  }
}

void Controller::showSala() {
  // QTableWidget sala(2, 3);
  bigliettoView->getSalaView();
}

void Controller::loadUsers(bool canUpdate) {
  QFile file;
  QVariantList *list = readUtenti(file, canUpdate);
  if (list != nullptr) {
    popolaVectorUtenti(*list);
    view->createLayoutSetup();

    QFileInfo info(file.fileName());
    view->setLabelPathUser(info.fileName());
  }
}

void Controller::loadFamilies(bool canUpdate) {
  QFile file;
  QVariantList *list = readFamiglie(file, canUpdate);
  if (list != nullptr) {
    popolaVectorFamiglie(*list);
    view->createLayoutSetup();

    QFileInfo info(file.fileName());
    view->setLabelPathFamiglie(info.fileName());
  }
}

void Controller::loadEntrate(bool canUpdate) {
  QFile file;
  QVariantList *list = readEntrata(file, canUpdate);
  if (list != nullptr) {
    popolaVectorEntrate(*list);
    view->createLayoutSetup();

    QFileInfo info(file.fileName());
    view->setLabelPathEntrata(info.fileName());
  }
}

void Controller::loadPostiOccupati(bool canUpdate) {
  QFile file;
  QVariantList *list = readPosti(file, canUpdate);
  if (list != nullptr) {
    qDebug() << "cose";
  }
}

void Controller::loadSale(bool canUpdate) {
  QFile file;
  QVariantList *list = readSale(file, canUpdate);
  if (list != nullptr) {
    popolaVectorSale(*list);
    QFileInfo info(file.fileName());
    view->setLabelPathSale(info.fileName());
  }
}

void Controller::loadFilm(bool canUpdate) {
  QFile file;
  QJsonObject *obj = readFilm(file, canUpdate);
  if (obj != nullptr) {
    filmObj = *obj;
  }
}

QVariantList *Controller::readUtenti(QFile &file, bool canUpdate) {
  if (pathJsonUsers == "" || canUpdate) {
    pathJsonUsers = QFileDialog::getOpenFileName(
        view, tr("Carica json Utenti"), "/home/student/QTheater/json",
        tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }
  if (pathJsonUsers != "") {
    file.setFileName(pathJsonUsers);

    if (!file.open(QIODevice::ReadOnly)) {
      openError(QString("File open error: Read"));
    } else {
      model->clearVectorUtenti();

      QString json = file.readAll();

      QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));
      if (!doc.isEmpty()) {
        QJsonObject jObj = doc.object();

        QVariantMap mainMap = jObj.toVariantMap();
        QVariantList *localList = new QVariantList();
        *localList = mainMap["Utenti"].toList();
        view->changeTitleChooseUtenti("Cambia file json per utenti");

        return localList;
      } else {
        openError(QString("File vuoto"));
      }
    }
  }

  return nullptr;
}

QVariantList *Controller::readFamiglie(QFile &file, bool canUpdate) {
  if (pathJsonFamiglie == "" || canUpdate) {
    pathJsonFamiglie = QFileDialog::getOpenFileName(
        view, tr("Carica json Famiglie"), "/home/student/QTheater/json",
        tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }

  if (pathJsonFamiglie != "") {
    file.setFileName(pathJsonFamiglie);

    if (!file.open(QIODevice::ReadOnly)) {
      openError(QString("File open error: Read"));
    } else {
      model->clearVectorFamiglie();

      QString json = file.readAll();

      QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));
      if (!doc.isEmpty()) {
        QJsonObject jObj = doc.object();

        QVariantMap mainMap = jObj.toVariantMap();
        QVariantList *localList = new QVariantList();
        *localList = mainMap["Famiglie"].toList();
        view->changeTitleChooseFamiglie("Cambia file json per Famiglie");

        return localList;
      } else {
        openError(QString("File vuoto"));
      }
    }
  }

  return nullptr;
}

QVariantList *Controller::readEntrata(QFile &file, bool canUpdate) {
  if (pathJsonEntrata == "" || canUpdate) {
    pathJsonEntrata = QFileDialog::getOpenFileName(
        view, tr("Carica json Entrate"), "/home/student/QTheater/json",
        tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }

  if (pathJsonEntrata != "") {
    file.setFileName(pathJsonEntrata);

    if (!file.open(QIODevice::ReadOnly)) {
      openError(QString("File open error: Read"));
    } else {
      model->clearVectorEntrate();

      QString json = file.readAll();

      QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));
      if (!doc.isEmpty()) {
        QJsonObject jObj = doc.object();

        QVariantMap mainMap = jObj.toVariantMap();
        QVariantList *localList = new QVariantList();
        *localList = mainMap["Entrate"].toList();
        view->changeTitleChooseEntrata("Cambia file json per Entrate");

        return localList;
      } else {
        openError(QString("File vuoto"));
      }
    }
  }

  return nullptr;
}

QVariantList *Controller::readPosti(QFile &file, bool canUpdate) {
  if (pathJsonPosti == "" || canUpdate) {
    pathJsonPosti = QFileDialog::getOpenFileName(
        view, tr("Carica json Posti"), "/home/student/QTheater/json",
        tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }
  if (pathJsonPosti != "") {
    file.setFileName(pathJsonPosti);

    if (!file.open(QIODevice::ReadOnly)) {
      openError(QString("File open error: Read"));
    } else {
      qDebug() << "ciao:)";

      QString json = file.readAll();

      QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));
      if (!doc.isEmpty()) {
        QJsonObject jObj = doc.object();

        QVariantMap mainMap = jObj.toVariantMap();
        QVariantList *localList = new QVariantList();
        *localList = mainMap["Posti"].toList();

        return localList;
      } else {
        openError(QString("File vuoto"));
      }
    }
  }

  return nullptr;
}

QVariantList *Controller::readSale(QFile &file, bool canUpdate) {
  if (pathJsonSale == "" || canUpdate) {
    pathJsonSale = QFileDialog::getOpenFileName(
        view, tr("Carica json Sale"), "/home/student/QTheater/json",
        tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }
  if (pathJsonSale != "") {
    file.setFileName(pathJsonSale);

    if (!file.open(QIODevice::ReadOnly)) {
      openError(QString("File open error: Read"));
    } else {
      model->cleaVectorSale();

      QString json = file.readAll();

      QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));

      if (!doc.isEmpty()) {
        QJsonObject jObj = doc.object();

        QVariantMap mainMap = jObj.toVariantMap();
        QVariantList *localList = new QVariantList();

        *localList = mainMap["Sale"].toList();
        view->changeTitleChooseSala("Cambia file json per sale");

        return localList;
      } else {
        openError(QString("File vuoto"));
      }
    }
  }

  return nullptr;
}

QJsonObject *Controller::readFilm(QFile &file, bool canUpdate) {
  if (pathJsonFilm == "" || canUpdate) {
    pathJsonFilm = QFileDialog::getOpenFileName(
        view, tr("Carica json Posti"), "/home/student/QTheater/json",
        tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }

  if (pathJsonFilm != "") {
    file.setFileName(pathJsonFilm);

    if (!file.open(QIODevice::ReadOnly)) {
      openError(QString("File open error: Read"));
    } else {
      qDebug() << "ciao:)";

      QString json = file.readAll();

      QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));
      if (!doc.isEmpty()) {
        QJsonObject *jObj = new QJsonObject;

        *jObj = doc.object();

        return jObj;

      } else {
        openError(QString("File vuoto"));
      }
    }
  }

  return nullptr;
}

void Controller::popolaVectorUtenti(const QVariantList &list) {
  for (int i = 0; i < list.length(); ++i) {
    QVariantMap map = list[i].toMap();
    string cf = map["CF"].toString().toStdString();
    if (!model->searchCf(cf)) {
      model->addUtente(new Utente(cf, map["name"].toString().toStdString(),
                                  map["surname"].toString().toStdString(),
                                  static_cast<unsigned int>(map["age"].toInt()),
                                  map["tel.Num"].toString().toStdString()));
    }
  }
}

void Controller::popolaVectorPosti(const QVariantList &list) {}

void Controller::popolaVectorFamiglie(const QVariantList &list) {
  Famiglia *fam = nullptr;

  for (int i = 0; i < list.length(); ++i) {
    QVariantMap map = list[i].toMap();

    string name = map["Name"].toString().toStdString();

    if (!model->searchNameFamiglia(name)) {
      fam = new Famiglia(name);
      for (int j = 1; j < map.size(); j++) {
        QString key = QString::fromStdString("Utente" + std::to_string(j));
        string cf = map[key].toString().toStdString();
        Utente *u = model->getUtente(cf);
        fam->addMembro(u);
      }
      model->addFamiglia(fam);
    }
  }
}

void Controller::popolaVectorEntrate(const QVariantList &list) {
  for (int i = 0; i < list.length(); ++i) {
    //    qDebug() << " i for popola " << i;
    QVariantMap map = list[i].toMap();

    QString tipo = map["Tipo"].toString();

    if (tipo == "Abbonamento") {
      if (model->searchCf(map["Utente"].toString().toStdString())) {
        if (map["Codice"].toUInt() > codAbb) codAbb = map["Codice"].toUInt();

        model->addEntrata(
            new Abbonamento(new Data(map["Data"].toString().toStdString()),
                            map["Utente"].toString().toStdString(), 7.5,
                            map["Codice"].toString().toStdString(),
                            map["Entrate_rimaste"].toInt()));
      }
    }

    else if (tipo == "Abbonamento_Famigliare") {
      if (model->searchCf(map["Utente"].toString().toStdString()) &&
          model->searchNameFamiglia(map["Famiglia"].toString().toStdString())) {
        if (map["Codice"].toUInt() > codAbbFam)
          codAbbFam = map["Codice"].toUInt();

        model->addEntrata(new AbbonamentoFamigliare(
            new Data(map["Data"].toString().toStdString()),
            map["Utente"].toString().toStdString(),
            map["Famiglia"].toString().toStdString(), 7.5,
            map["Codice"].toString().toStdString(),
            map["Entrate_rimaste"].toInt()));
      }
    }

    else if (tipo == "Biglietto") {
      if (model->searchCf(map["Utente"].toString().toStdString())) {
        model->addEntrata(new Biglietto(
            map["Codice"].toString().toStdString(),
            new Data(map["Data"].toString().toStdString()),
            map["Utente"].toString().toStdString(), 7.5,
            map["Riduzione"].toBool(), map["Film"].toString().toStdString()));
      }
    }
  }
}

void Controller::popolaVectorSale(const QVariantList &list) {
  Sala *s = nullptr;
  for (int i = 0; i < list.length(); ++i) {
    QVariantMap map = list[i].toMap();
    s = new Sala((map["righe"].toUInt()), (map["colonne"].toUInt()),
                 map["nome_sala"].toString().toStdString());
    model->addSala(s);
  }
}

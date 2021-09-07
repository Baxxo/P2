#include "controller.h"

#include <QDate>
#include <QFileDialog>
#include <QTimer>

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
      cod(0),
      abbFam(nullptr),
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
    if (model->removeEntrata(cod.toStdString())) {
      removeAbbonamentoFromJson(cod);
    }
    return true;
  }
  return false;
}

#include <QDebug>

void Controller::removeAbbonamentoFromJson(const QString &cod) {
  QFile file(pathJsonEntrata);
  file.open(QIODevice::ReadOnly);

  QJsonDocument jsonOrg = QJsonDocument::fromJson(file.readAll());
  file.close();

  QJsonValue v = jsonOrg.object().value(QString("Entrate"));

  QJsonValue a = v.toObject().value("Entrate Abbonamento");

  QJsonObject objectV = v.toObject();

  QJsonObject objectA = a.toObject();

  //  qDebug() << cod;

  //  for (auto it = objectA.begin(); it != objectA.end(); ++it) {
  //    qDebug() << it.key() << " " << (it.key() == cod);
  //  }

  objectA.remove(cod);

  objectV.insert("Entrate Abbonamento", objectA);

  QJsonObject obj;
  obj.insert("Entrate", objectV);

  QJsonDocument doc(obj);

  if (!file.open(QIODevice::WriteOnly)) {
    openError(QString("File open error: Write"));
  }

  file.write(doc.toJson());
  file.close();
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
                          cf.toStdString(), 7.5, std::to_string(++cod), 10);

    model->addEntrata(abb);

    QFile file(pathJsonEntrata);
    if (!file.open(QIODevice::ReadOnly)) {
      openError(QString("File open error: Read"));
    }

    QJsonDocument jsonOrg = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonValue v = jsonOrg.object().value(QString("Entrate"));

    QJsonValue a = v.toObject().value("Entrate Abbonamento");

    QJsonObject objectV = v.toObject();

    QJsonObject objectA = a.toObject();

    QJsonObject newAbbonamento;
    newAbbonamento.insert("Tipo", "Abbonamento");
    newAbbonamento.insert("Data",
                          QString::fromStdString(abb->getData()->toString()));
    newAbbonamento.insert("Utente", QString::fromStdString(abb->getUtente()));
    newAbbonamento.insert("Codice", QString::fromStdString(abb->getCodice()));
    newAbbonamento.insert("Entrate_rimaste", abb->getEntrate());

    objectA.insert(QString::fromStdString(abb->getCodice()), newAbbonamento);

    objectV.insert("Entrate Abbonamento", objectA);

    QJsonObject obj;
    obj.insert("Entrate", objectV);

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
          cf.toStdString(), name.toStdString(), 7.5, std::to_string(++cod), 10,
          model->getFamiglia(name.toStdString())->getSize());

      model->addEntrata(abbFam);

      QFile file(pathJsonEntrata);
      if (!file.open(QIODevice::ReadOnly)) {
        openError(QString("File open error: Read"));
      }

      QJsonDocument jsonOrg = QJsonDocument::fromJson(file.readAll());
      file.close();

      QJsonValue a = jsonOrg.object().value(QString("Entrate"));

      QJsonValue v = a.toObject().value("Entrate Abbonamento");

      QJsonObject objectV = v.toObject();

      QJsonObject objectA = a.toObject();

      QJsonObject newAbbonamento;
      newAbbonamento.insert("Tipo", "Abbonamento_Famigliare");
      newAbbonamento.insert(
          "Data", QString::fromStdString(abbFam->getData()->toString()));
      newAbbonamento.insert("Utente",
                            QString::fromStdString(abbFam->getUtente()));
      newAbbonamento.insert("Famiglia",
                            QString::fromStdString(abbFam->getFamiglia()));
      newAbbonamento.insert("Codice",
                            QString::fromStdString(abbFam->getCodice()));
      newAbbonamento.insert("Entrate_rimaste", abbFam->getEntrate());

      objectV.insert(QString::fromStdString(abbFam->getCodice()),
                     newAbbonamento);

      objectA.insert("Entrate Abbonamento", objectV);

      QJsonObject obj;
      obj.insert("Entrate", objectA);

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
  //  for (auto it = model->getListUtenti().cbegin();
  //       it != model->getListUtenti().cend(); ++it) {
  //    string s = (**it).getSurname() + " " + (**it).getName() + " ( " +
  //               (**it).getCodFisc() + " )";
  //    admin->addUtenteinList(QString(s.c_str()));
  //  }

  for (unsigned int i = 0; i < model->sizeUtenti(); ++i) {
    Utente *tmp = model->getUser(i);
    string s = (*tmp).getSurname() + " " + (*tmp).getName() + " ( " +
               (*tmp).getCodFisc() + " )";
    admin->addUtenteinList(QString::fromStdString(s));
  }
}

void Controller::addUteneAdmin(const QString &s) { admin->addUtenteinList(s); }

void Controller::loadFamiglieInAdmin() {
  admin->clearListFamiglie();
  //  for (auto it = model->getListFamiglie().cbegin();
  //       it != model->getListFamiglie().cend(); ++it) {
  //    admin->addFamigliainList(QString::fromStdString(
  //        (*it)->getName() + " (membri: " + std::to_string((*it)->getSize()) +
  //        " )"));
  //  }

  for (unsigned int i = 0; i < model->sizeFamilies(); ++i) {
    Famiglia *tmp = model->getFamily(i);
    string s =
        tmp->getName() + " (membri: " + std::to_string(tmp->getSize()) + " )";
    admin->addFamigliainList(QString::fromStdString(s));
  }
}

void Controller::loadEntrateInAdmin() {
  admin->clearListEntrate();

  //  for (auto it = model->getListEntrate().cbegin();
  //       it != model->getListEntrate().cend(); ++it) {
  //    Abbonamento *ab = dynamic_cast<Abbonamento *>(&(**it));

  //    AbbonamentoFamigliare *abf = dynamic_cast<AbbonamentoFamigliare *>(ab);
  //    if (abf) {
  //      admin->addAbbonamento("Abbonamento Famigliare -> " +
  //                                QString::fromStdString(abf->toString()),
  //                            QString::fromStdString(abf->getCodice()));

  //    } else if (ab) {
  //      Utente *u_tmp = model->getUtente(ab->getUtente());
  //      string s1 = "Abbonamento -> " + u_tmp->toString();
  //      string s2 = ab->getCodice();
  //      admin->addAbbonamento(QString::fromStdString(s1),
  //                            QString::fromStdString(s2));
  //    }
  //  }

  for (unsigned int i = 0; i < model->sizeEntrate(); ++i) {
    Abbonamento *ab = dynamic_cast<Abbonamento *>(model->getEntrata(i));

    AbbonamentoFamigliare *abf = dynamic_cast<AbbonamentoFamigliare *>(ab);
    if (abf) {
      admin->addAbbonamento("Abbonamento Famigliare -> " +
                                QString::fromStdString(abf->toString()),
                            QString::fromStdString(abf->getCodice()));

    } else if (ab) {
      Utente *u_tmp = model->getUtente(ab->getUtente());
      string s1 = "Abbonamento -> " + u_tmp->toString();
      string s2 = ab->getCodice();
      admin->addAbbonamento(QString::fromStdString(s1),
                            QString::fromStdString(s2));
    }
  }
}

void Controller::loadSaleInAdmin() {
  admin->clearListSale();
  //  for (auto it = model->getListSale().cbegin();
  //       it != model->getListSale().cend(); ++it) {
  //    admin->addSaleinList(QString::fromStdString((**it).getNomesala()));
  //  }

  for (unsigned int i = 0; i < model->sizeSale(); ++i) {
    Sala *tmp = model->getSala_byPos(i);
    admin->addSaleinList(QString::fromStdString(tmp->getNomesala()));
  }
}

void Controller::loadFilmInAdmin() {
  admin->clearListFilm();
  QJsonObject obj = filmObj.begin().value().toObject();
  for (auto it = obj.begin(); it != obj.end(); ++it) {
    admin->addFilminList((it).key());
  }
}

void Controller::loadFilmInBigliettoview() {
  bigliettoView->clearListFilm();
  QJsonObject obj = filmObj.begin().value().toObject();
  for (auto it = obj.begin(); it != obj.end(); ++it) {
    bigliettoView->addFilminList((it).key());
  }
}

void Controller::popolaEntrateBiglietto(int index) {
  switch (index) {
    case 0:
      bigliettoView->setTitleSearch("Utente");
      //      for (auto it = model->getListUtenti().cbegin();
      //           it != model->getListUtenti().cend(); ++it) {
      //        bigliettoView->addEntrataToLista(
      //            QString::fromStdString((*it)->toString()),
      //            QString::fromStdString((*it)->getCodFisc()));
      //      }

      for (unsigned int i = 0; i < model->sizeUtenti(); ++i) {
        Utente *tmp = model->getUser(i);
        bigliettoView->addEntrataToLista(
            QString::fromStdString(tmp->toString()),
            QString::fromStdString(tmp->getCodFisc()));
      }
      break;
    case 1:
      bigliettoView->setTitleSearch("Abbonamento");
      //      for (auto it = model->getListEntrate().cbegin();
      //           it != model->getListEntrate().cend(); ++it) {
      //        try {
      //          Abbonamento &dumb = dynamic_cast<Abbonamento &>(**it);
      //          bigliettoView->addEntrataToLista(
      //              QString::fromStdString(dumb.toString()),
      //              QString::fromStdString(dumb.getCodice()));
      //        } catch (std::bad_cast e) {
      //        }
      //      }

      for (unsigned int i = 0; i < model->sizeEntrate(); ++i) {
        try {
          Abbonamento &dumb =
              dynamic_cast<Abbonamento &>(*model->getEntrata(i));
          bigliettoView->addEntrataToLista(
              QString::fromStdString(dumb.toString()),
              QString::fromStdString(dumb.getCodice()));
        } catch (std::bad_cast e) {
        }
      }
      break;
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

  if (pathJsonPosti == "") loadPostiOccupati();

  if (pathJsonSale == "") loadSale();
  loadSaleInAdmin();

  if (pathJsonFilm == "") loadFilm();
  loadFilmInAdmin();

  admin->show();
}

void Controller::openClient() {
  if (!client) {
    client = new Client(this);
  }

  QTimer::singleShot(0, client, SLOT(resizeMe()));
  client->show();
}

void Controller::openUtente() {
  if (!utente) {
    utente = new Utente_View(this);
  }

  if (pathJsonUsers == "") loadUsers();

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
  //  for (auto it = model->getListUtenti().cbegin();
  //       it != model->getListUtenti().cend(); ++it) {
  //    QString text =
  //        QString::fromStdString(((*it)->getSurname() + " " + (*it)->getName()
  //        +
  //                                " ( " + (*it)->getCodFisc() + " )")
  //                                   .c_str());
  //    QString cf = QString::fromStdString(((*it)->getCodFisc()).c_str());
  //    famigliaView->addUtenteToLista(text, cf);
  //  }

  for (unsigned int i = 0; i < model->sizeUtenti(); ++i) {
    Utente *tmp = model->getUser(i);
    QString text =
        QString::fromStdString((tmp->getSurname() + " " + tmp->getName() +
                                " ( " + tmp->getCodFisc() + " )")
                                   .c_str());
    QString cf = QString::fromStdString((tmp->getCodFisc()).c_str());
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
  if (pathJsonFamiglie == "") loadFamilies();
  if (pathJsonEntrata == "") loadEntrate();

  abbonamentoView->clearListUtenti();
  //  for (auto it = model->getListUtenti().cbegin();
  //       it != model->getListUtenti().cend(); ++it) {
  //    abbonamentoView->addUtente(
  //        QString::fromStdString((*it)->getSurname() + " " + (*it)->getName()
  //        +
  //                               " ( " + (*it)->getCodFisc() + " )"),
  //        QString::fromStdString((*it)->getCodFisc()));
  //  }
  for (unsigned int i = 0; i < model->sizeUtenti(); ++i) {
    Utente *tmp = model->getUser(i);
    abbonamentoView->addUtente(
        QString::fromStdString(tmp->getSurname() + " " + tmp->getName() +
                               " ( " + tmp->getCodFisc() + " )"),
        QString::fromStdString(tmp->getCodFisc()));
  }

  if (pathJsonFamiglie == "") loadFamilies();

  abbonamentoView->clearListFamiglie();
  //  for (auto it = model->getListFamiglie().cbegin();
  //       it != model->getListFamiglie().cend(); ++it) {
  //    abbonamentoView->addFamiglia(
  //        QString::fromStdString((*it)->getName() + " (membri: " +
  //                               std::to_string((*it)->getSize()) + " )"),
  //        QString::fromStdString((*it)->getName()));
  //  }

  for (unsigned int i = 0; i < model->sizeFamilies(); ++i) {
    Famiglia *tmp = model->getFamily(i);
    abbonamentoView->addFamiglia(
        QString::fromStdString(tmp->getName() + " (membri: " +
                               std::to_string(tmp->getSize()) + " )"),
        QString::fromStdString(tmp->getName()));
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
  if (pathJsonEntrata == "") loadEntrate();
  if (pathJsonPosti == "") loadPostiOccupati();
  if (pathJsonSale == "") loadSale();
  if (pathJsonFilm == "") loadFilm();

  QTimer::singleShot(0, bigliettoView, SLOT(resizeMe()));

  if (pathJsonFilm == "") loadFilm();
  loadFilmInBigliettoview();

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

// void Controller::loadEntrateSlot() { loadEntrateinView(true); }
void Controller::loadEntrateSlot() { loadEntrate(true); }

void Controller::loadPostiSlot() { loadPostiOccupati(true); }

void Controller::loadSaleSlot() { loadSale(true); }

void Controller::loadFilmSlot() { loadFilm(true); }

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
  if (pathJsonFilm == "") {
    pathJsonFilm = QFileDialog::getOpenFileName(
        view, tr("Carica json Film"), "/home/student/QTheater/json",
        tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }
  QFile file(pathJsonFilm);
  if (!file.open(QIODevice::ReadWrite)) {
    openError(QString("File open error: Read"));
  }

  QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
  file.close();
  QJsonObject obj = doc.object();

  QJsonValue film = obj.value("Film");

  QJsonObject mstObj = film.toObject();

  mstObj.insert(admin->getNomeFilm(), admin->getSalaFilm());

  obj.insert("Film", mstObj);

  if (file.open(QIODevice::WriteOnly)) {
    doc.setObject(obj);
    file.write(doc.toJson());
    file.close();
    admin->setUtilityFilm("Film inserito correttamente");
  } else {
    openError(QString("File open error: Write"));
  }
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
  model->addSala(new Sala(admin->getRigheSala().toInt(), admin->getColonneSala().toInt(), admin->getNomeSala().toStdString()));
  array.push_back(newSala);

  QJsonObject obj;
  obj.insert("Sale", array);

  QJsonDocument doc(obj);

  if (!file.open(QIODevice::WriteOnly)) {
    openError(QString("File open error: Write"));
  }

  file.write(doc.toJson());
  file.close();

  // aggiunta di array vuoto in json posti
  QFile filePosti(pathJsonPosti);
  if (!filePosti.open(QIODevice::ReadWrite)) {
    openError(QString("File open error: Read"));
  }

  QJsonDocument docPosti;
  QJsonArray *arrayVuoto = new QJsonArray;
  QJsonObject objP;
  objP=postiObj.value("Posti").toObject();
  objP.insert(admin->getNomeSala(), *arrayVuoto);
  postiObj.insert("Posti", objP);

  if (arrayVuoto) {
    delete arrayVuoto;
  }
  docPosti.setObject(postiObj);
  filePosti.write(docPosti.toJson());
  filePosti.close();

  loadSaleInAdmin();

}

void Controller::newPostoOccupato() {
  QFile file(pathJsonPosti);
  if (!file.open(QIODevice::ReadWrite)) {
    openError(QString("File open error: Read"));
  }
  QJsonDocument doc;
  QJsonArray *array = new QJsonArray;
  QJsonObject obj;
  obj=postiObj.value("Posti").toObject();
  auto it = postiObj.value("Posti").toObject().value(bigliettoView->getNomeSala()).toArray();
  *array = it;
  array->append(
      bigliettoView->getCurrentColumn() +
      (bigliettoView->getCurrentRow() * bigliettoView->getColonneMax()));

  obj.insert(bigliettoView->getNomeSala(), *array);
  //postiObj.insert(bigliettoView->getNomeSala(), *array);
  postiObj.insert("Posti", obj);

  doc.setObject(postiObj);
  file.write(doc.toJson());
  file.close();
}

void Controller::setPostiOccupati() {
  QString s = bigliettoView->getNomeSala();  
  auto it = postiObj.value("Posti").toObject().value(s).toArray();
  QJsonArray *array = new QJsonArray;
  *array = it;
  QString regola = admin->getRegola();
  int row, column;
  for (int i = 0; i < array->size(); ++i) {
    row = array->at(i).toInt() / bigliettoView->getColonneMax();
    column = (array->at(i).toInt()) % bigliettoView->getColonneMax();
    bigliettoView->setPostoOccupato(row, column, regola);
  }
}

void Controller::stpBigl() {
  if (bigliettoView->getTipologia() == "Biglietto") {
    QString utente = bigliettoView->getSelectName();
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
  }
}

void Controller::showSala() {
  QString s = bigliettoView->getSelectedFilm();
  QJsonObject obj = filmObj.begin().value().toObject();
  QString f = obj.find(s).value().toString();
  unsigned int rows = 0, columns = 0;
  //  for (auto it = model->getListSale().cbegin();
  //       it != model->getListSale().cend(); ++it) {
  //    if (QString::fromStdString((**it).getNomesala()) == f) {
  //      rows = (**it).getRighe();
  //      columns = (**it).getColonne();
  //    }
  //  }

  for (unsigned int i = 0; i < model->sizeSale(); ++i) {
    Sala *tmp = model->getSala_byPos(i);

    if (QString::fromStdString(tmp->getNomesala()) == f) {
      rows = tmp->getRighe();
      columns = tmp->getColonne();
    }
  }
  bigliettoView->createSalaView(rows, columns, f);
}

void Controller::buyBiglietto() {
  QFile file(pathJsonEntrata);
  if (!file.open(QIODevice::ReadOnly)) {
    openError(QString("File open error: Read"));
  }
  QJsonDocument jsonOrg = QJsonDocument::fromJson(file.readAll());
  file.close();

  QJsonValue v = jsonOrg.object().value(QString("Entrate"));

  QJsonValue vb = v.toObject().value(QString("Entrate Singole"));

  QJsonValue va = v.toObject().value(QString("Entrate Abbonamento"));

  QJsonObject oB = vb.toObject();

  QJsonObject oA = va.toObject();

  if (bigliettoView->getTipologia() == "Biglietto") {
    QString cf = bigliettoView->getSelectName();
    //    for (auto it = model->getListUtenti().cbegin();
    //         it != model->getListUtenti().cend(); ++it) {
    //      if (cf == QString::fromStdString((**it).getCodFisc())) {
    //        cod++;
    //        QDate *d = new QDate;
    //        Data *date = new Data(d->currentDate().year(),
    //        d->currentDate().month(),
    //                              d->currentDate().day());
    //        bool riduzione = false;
    //        if ((**it).getAge() < 14) riduzione = true;
    //        Biglietto *b = new Biglietto(
    //            std::to_string(cod), date, (**it).getCodFisc(), 7.5,
    //            riduzione, bigliettoView->getSelectedFilm().toStdString());

    //        QJsonObject newUser;
    //        newUser.insert("Codice", QString::number(cod));
    //        newUser.insert("Data", QString::fromStdString(date->toString()));
    //        newUser.insert("CF", QString::fromStdString((**it).getCodFisc()));
    //        newUser.insert("Film", bigliettoView->getSelectedFilm());
    //        newUser.insert("Prezzo", QString::number(b->getPrezzo()));
    //        newUser.insert("Riduzione", QString::number(riduzione));
    //        newUser.insert("Tipo", "Biglietto");

    //        oB.insert(QString::number(cod), newUser);

    //        model->addEntrata(b);
    //      }

    for (unsigned int i = 0; i < model->sizeUtenti(); ++i) {
      Utente *tmp = model->getUser(i);
      if (cf == QString::fromStdString(tmp->getCodFisc())) {
        cod++;
        QDate *d = new QDate;
        Data *date = new Data(d->currentDate().year(), d->currentDate().month(),
                              d->currentDate().day());
        bool riduzione = false;
        if (tmp->getAge() < 14) riduzione = true;
        Biglietto *b = new Biglietto(
            std::to_string(cod), date, tmp->getCodFisc(), 7.5, riduzione,
            bigliettoView->getSelectedFilm().toStdString());

        QJsonObject newUser;
        newUser.insert("Codice", QString::number(cod));
        newUser.insert("Data", QString::fromStdString(date->toString()));
        newUser.insert("CF", QString::fromStdString(tmp->getCodFisc()));
        newUser.insert("Film", bigliettoView->getSelectedFilm());
        newUser.insert("Prezzo", QString::number(b->getPrezzo()));
        newUser.insert("Riduzione", QString::number(riduzione));
        newUser.insert("Tipo", "Biglietto");

        oB.insert(QString::number(cod), newUser);

        model->addEntrata(b);
      }
    }
  }

  if (bigliettoView->getTipologia() == "Abbonamento") {
    QString cod = bigliettoView->getSelectName();

    for (unsigned int i = 0; i < model->sizeEntrate(); ++i) {
      //      }
      //    for (auto it = model->getListEntrate().cbegin();
      //         it != model->getListEntrate().cend(); ++it) {
      //      if (cod == QString::fromStdString((**it).getCodice())) {
      //        Abbonamento *ab = dynamic_cast<Abbonamento *>(&(**it));
      if (cod == QString::fromStdString(model->getEntrata(i)->getCodice())) {
        Abbonamento *ab = dynamic_cast<Abbonamento *>(model->getEntrata(i));

        AbbonamentoFamigliare *abf = dynamic_cast<AbbonamentoFamigliare *>(ab);
        if (abf) {
          QDate *d = new QDate;
          QString date = d->currentDate().toString();

          QJsonObject newAbbonamento;
          newAbbonamento.insert("Tipo", "Abbonamento Famigliare");
          newAbbonamento.insert("Data", date);
          newAbbonamento.insert("Utente",
                                QString::fromStdString(abf->getUtente()));
          newAbbonamento.insert("Codice",
                                QString::fromStdString(abf->getCodice()));
          newAbbonamento.insert("Famiglia",
                                QString::fromStdString(abf->getFamiglia()));
          newAbbonamento.insert("Entrate_rimaste", abf->getEntrate() - 1);

          oA.insert(QString::fromStdString(abf->getCodice()), newAbbonamento);
        }
        if (ab) {
          QDate *d = new QDate;
          QString date = d->currentDate().toString();

          QJsonObject newAbbonamento;
          newAbbonamento.insert("Tipo", "Abbonamento");
          newAbbonamento.insert("Data", date);
          newAbbonamento.insert("Utente",
                                QString::fromStdString(ab->getUtente()));
          newAbbonamento.insert("Codice",
                                QString::fromStdString(ab->getCodice()));
          newAbbonamento.insert("Entrate_rimaste", ab->getEntrate() - 1);

          oA.insert(QString::fromStdString(ab->getCodice()), newAbbonamento);

          // ab->removeOneEntrata();
        } else {
          //          qDebug() << "nessun abbonamento con quell'utente";
        }
      }
    }
  }

  QJsonObject o;
  o.insert("Entrate Singole", oB);
  o.insert("Entrate Abbonamento", oA);
  QJsonObject obj;
  obj.insert("Entrate", o);

  QJsonDocument doc1(obj);

  if (!file.open(QIODevice::WriteOnly)) {
    openError(QString("File open error: Write"));
  }

  file.write(doc1.toJson());
  file.close();

  //    for(auto i= model->getListEntrate().cbegin();
  //    i!=model->getListEntrate().cend(); ++i){
  //        if((**i).getUtente()== bigliettoView->getSearch().toStdString()){
  //        }
  //    }
}

void Controller::loadUsers(bool canUpdate) {
  QFile file;
  QVariantList *list = readUtenti(file, canUpdate);
  if (list != nullptr) {
    popolaVectorUtenti(*list);
    view->showLayoutSetup();

    QFileInfo info(file.fileName());
    view->setLabelPathUser(info.fileName());
  }
}

void Controller::loadFamilies(bool canUpdate) {
  QFile file;
  QVariantList *list = readFamiglie(file, canUpdate);
  if (list != nullptr) {
    popolaVectorFamiglie(*list);
    view->showLayoutSetup();
    QFileInfo info(file.fileName());
    view->setLabelPathFamiglie(info.fileName());
  }
}
void Controller::loadEntrate(bool canUpdate) {
  QFile file;
  QVariantMap *map = readEntrata(file, canUpdate);
  if (map != nullptr) {
    popolaVectorEntrate(*map);
    view->showLayoutSetup();
    QFileInfo info(file.fileName());
    view->setLabelPathEntrata(info.fileName());
  }
}

void Controller::loadPostiOccupati(bool canUpdate) {
  QFile file;
  QJsonObject *obj = readPosti(file, canUpdate);
  if (obj != nullptr) {
    postiObj = *obj;

    QFileInfo info(file.fileName());
    view->setLabelPathPosti(info.fileName());
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
  if (obj) {
    filmObj = *obj;

    QFileInfo info(file.fileName());
    view->setLabelPathFilm(info.fileName());
  }
}

QVariantList *Controller::readUtenti(QFile &file, bool canUpdate) {
  do {
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
          QJsonObject jObj_temp = doc.object();

          QVariantMap mainMap = jObj_temp.toVariantMap();
          QVariantList *localList = new QVariantList();
          *localList = mainMap["Utenti"].toList();

          if (localList->size() > 0) {
            view->changeTitleChooseUtenti("Cambia file json per utenti");
            return localList;
          }

        } else {
          openError(QString("File vuoto"));
        }
      }
    }
  } while (pathJsonUsers != "");

  return nullptr;
}

QVariantList *Controller::readFamiglie(QFile &file, bool canUpdate) {
  do {
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
          QJsonObject jObj_temp = doc.object();

          QVariantMap mainMap = jObj_temp.toVariantMap();
          QVariantList *localList = new QVariantList();
          *localList = mainMap["Famiglie"].toList();

          if (localList->size() > 0) {
            view->changeTitleChooseFamiglie("Cambia file json per Famiglie");
            return localList;
          }
        } else {
          openError(QString("File vuoto"));
        }
      }
    }
  } while (pathJsonFamiglie != "");

  return nullptr;
}

QVariantMap *Controller::readEntrata(QFile &file, bool canUpdate) {
  do {
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
          QJsonObject jObj_temp = doc.object();

          QVariantMap mainMap = jObj_temp.toVariantMap();
          QVariantMap *localMap = new QVariantMap();
          *localMap = mainMap;

          if (localMap->size() > 0) {
            view->changeTitleChooseEntrata("Cambia file json per Entrate Film");
            return localMap;
          }
        } else {
          openError(QString("File vuoto"));
        }
      }
    }
  } while (pathJsonEntrata != "");

  return nullptr;
}

QJsonObject *Controller::readPosti(QFile &file, bool canUpdate) {
  do {
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
        QString json = file.readAll();

        QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));
        if (!doc.isEmpty()) {
          QJsonObject *jObj = new QJsonObject;

          *jObj = doc.object();

          if (jObj->size() > 0) {
            view->changeTitleChoosePosti("Cambia file json per Posti");

            return jObj;
          }

        } else {
          openError(QString("Empty file"));
        }
      }
    }
  } while (pathJsonPosti != "");
  return nullptr;
}

QVariantList *Controller::readSale(QFile &file, bool canUpdate) {
  do {
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
          QJsonObject jObj_temp = doc.object();

          QVariantMap mainMap = jObj_temp.toVariantMap();
          QVariantList *localList = new QVariantList();

          *localList = mainMap["Sale"].toList();

          if (localList->size() > 0) {
            view->changeTitleChooseSala("Cambia file json per Sale");

            return localList;
          }
        } else {
          openError(QString("File vuoto"));
        }
      }
    }
  } while (pathJsonSale != "");

  return nullptr;
}

QJsonObject *Controller::readFilm(QFile &file, bool canUpdate) {
  do {
    if (pathJsonFilm == "" || canUpdate) {
      pathJsonFilm = QFileDialog::getOpenFileName(
          view, tr("Carica json Film"), "/home/student/QTheater/json",
          tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
    }

    if (pathJsonFilm != "") {
      file.setFileName(pathJsonFilm);

      if (!file.open(QIODevice::ReadOnly)) {
        openError(QString("File open error: Read"));
      } else {
        QString json = file.readAll();

        QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));
        if (!doc.isEmpty()) {
          QJsonObject *jObj = new QJsonObject;
          *jObj = doc.object();

          QString tmpKey = jObj->begin().key();

          if (tmpKey == "Film") {
            view->changeTitleChooseFilm("Cambia file json per Film");

            return jObj;
          }
        } else {
          openError(QString("File vuoto"));
        }
      }
    }
  } while (pathJsonFilm != "");

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

#include <QDebug>
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

void Controller::popolaVectorEntrate(const QVariantMap &map) {
  QVariantMap listAbb;
  listAbb = map["Entrate"].toMap().value("Entrate Abbonamento").toMap();

  for (auto i = listAbb.cbegin(); i != listAbb.cend(); ++i) {
    QVariantMap mapA = (*i).toMap();
    QString tipo = mapA["Tipo"].toString();

    if (tipo == "Abbonamento") {
      if (model->searchCf(mapA["Utente"].toString().toStdString())) {
        if (mapA["Codice"].toUInt() > cod) cod = mapA["Codice"].toUInt();

        model->addEntrata(
            new Abbonamento(new Data(mapA["Data"].toString().toStdString()),
                            mapA["Utente"].toString().toStdString(), 7.5,
                            mapA["Codice"].toString().toStdString(),
                            mapA["Entrate_rimaste"].toInt()));
      }
    }

    else if (tipo == "Abbonamento_Famigliare") {
      if (model->searchCf(mapA["Utente"].toString().toStdString()) &&
          model->searchNameFamiglia(
              mapA["Famiglia"].toString().toStdString())) {
        if (mapA["Codice"].toUInt() > cod) cod = mapA["Codice"].toUInt();

        model->addEntrata(new AbbonamentoFamigliare(
            new Data(mapA["Data"].toString().toStdString()),
            mapA["Utente"].toString().toStdString(),
            mapA["Famiglia"].toString().toStdString(), 7.5,
            mapA["Codice"].toString().toStdString(),
            mapA["Entrate_rimaste"].toInt(),
            model->getFamiglia(mapA["Famiglia"].toString().toStdString())
                ->getSize()));
      }
    }
  }

  QVariantMap listSing;
  listSing = map["Entrate"].toMap().value("Entrate Singole").toMap();

  for (auto i = listSing.cbegin(); i != listSing.cend(); ++i) {
    QVariantMap mapB = (*i).toMap();

    if (model->searchCf(mapB["CF"].toString().toStdString())) {
      if (mapB["Codice"].toUInt() > cod) cod = mapB["Codice"].toUInt();

      model->addEntrata(new Biglietto(
          mapB["Codice"].toString().toStdString(),
          new Data(mapB["Data"].toString().toStdString()),
          mapB["CF"].toString().toStdString(), 7.5, mapB["Riduzione"].toBool(),
          mapB["Film"].toString().toStdString()));
    }
  }
}

void Controller::popolaVectorSale(const QVariantList &list) {
  Sala *s = nullptr;
  for (int i = 0; i < list.length(); ++i) {
    QVariantMap map = list[i].toMap();
    s = new Sala(static_cast<unsigned int>(map["righe"].toInt()),
                 static_cast<unsigned int>(map["colonne"].toInt()),
                 map["nome_sala"].toString().toUtf8().constData());
    model->addSala(s);
  }
}

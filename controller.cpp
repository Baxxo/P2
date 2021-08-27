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
      pathJsonAbbonamenti(""),
      objUtenti(nullptr),
      fam(nullptr),
      abb(nullptr),
      codAbb(0),
      abbFam(nullptr),
      codUt(0),
      codBigl(0),
      err(nullptr) {}

QString Controller::getPathJsonUsers() const { return pathJsonUsers; }

QString Controller::getPathJsonFamiglie() const { return pathJsonFamiglie; }

QString Controller::getPathJsonEntrata() const { return pathJsonEntrata; }

QString Controller::getPathJsonPosti() const { return pathJsonPosti; }

QString Controller::getPathJsonSale() const { return pathJsonSale; }

QString Controller::getPathJsonFilm() const { return pathJsonFilm; }

QString Controller::getPathJsonAbbonamenti() const {
  return pathJsonAbbonamenti;
}

bool Controller::removeAbbonamento(const QString &cod) {
  if (model->searchEntrata(cod.toStdString())) {
    return model->removeEntrata(cod.toStdString());
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
                          cf.toStdString(), 7.5, std::to_string(++codAbb), 10);

    model->addAbbonamento(abb);

    QFile file(pathJsonAbbonamenti);
    if (!file.open(QIODevice::ReadOnly)) {
      openError(QString("File open error: Read"));
    }

    QJsonDocument jsonOrg = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonValue v = jsonOrg.object().value(QString("Abbonamenti"));

    QJsonObject object = v.toObject();

    QJsonObject newAbbonamento;
    newAbbonamento.insert("Tipo", "Abbonamento");
    newAbbonamento.insert("Data",
                          QString::fromStdString(abb->getData()->ToString()));
    newAbbonamento.insert("Utente", QString::fromStdString(abb->getUtente()));
    newAbbonamento.insert("Codice", QString::fromStdString(abb->getCodice()));
    newAbbonamento.insert("Entrate_rimaste", abb->getEntrate());

    object.insert(QString::fromStdString(abb->getCodice()), newAbbonamento);

    QJsonObject obj;
    obj.insert("Abbonamenti", object);

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
          cf.toStdString(), name.toStdString(), 7.5, std::to_string(++codAbb),
          10);

      model->addAbbonamento(abbFam);

      QFile file(pathJsonAbbonamenti);
      if (!file.open(QIODevice::ReadOnly)) {
        openError(QString("File open error: Read"));
      }

      QJsonDocument jsonOrg = QJsonDocument::fromJson(file.readAll());
      file.close();

      QJsonValue v = jsonOrg.object().value(QString("Abbonamenti"));

      QJsonObject object = v.toObject();

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

      object.insert(QString::fromStdString(abb->getCodice()), newAbbonamento);

      QJsonObject obj;
      obj.insert("Abbonamenti", object);

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
    admin->addUtenteinList(QString(s.c_str()));
  }
}

void Controller::loadFamiglieInAdmin() {
  admin->clearListFamiglie();
  for (auto it = model->getListFamiglie().cbegin();
       it != model->getListFamiglie().cend(); ++it) {
    admin->addFamigliainList(QString::fromStdString(
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

void Controller::loadSaleInAdmin() {
  admin->clearListSale();
  for (auto it = model->getListSale().cbegin();
       it != model->getListSale().cend(); ++it) {
    admin->addSaleinList(QString::fromStdString((**it).getNomesala()));
  }
}

void Controller::loadFilmInAdmin() {
  admin->clearListFilm();
  for (auto it = filmObj.begin(); it != filmObj.end(); ++it) {
    admin->addFilminList((it).key());
  }
}

void Controller::loadAbbonamentiInAdmin() {
  admin->clearListAbbonamenti();
  for (auto it = model->getListAbbonamenti().cbegin();
       it != model->getListAbbonamenti().cend(); ++it) {
    Abbonamento *ab = dynamic_cast<Abbonamento *>(&(**it));

    AbbonamentoFamigliare *abf = dynamic_cast<AbbonamentoFamigliare *>(ab);
    if (abf) {
      admin->addAbbonamento("Abbonamento Famigliare " +
                                QString::fromStdString(abf->getFamiglia()),
                            QString::fromStdString(abf->getCodice()));

    } else {
      Utente *u_tmp = model->getUtente(ab->getUtente());
      string s1 = "Abbonamento " + u_tmp->toString();
      string s2 = ab->getCodice();
      admin->addAbbonamento(QString::fromStdString(s1),
                            QString::fromStdString(s2));
    }
  }
}

void Controller::loadFilmInBigliettoview() {
  bigliettoView->clearListFilm();
  for (auto it = filmObj.begin(); it != filmObj.end(); ++it) {
    bigliettoView->addFilminList((it).key());
  }
}

void Controller::popolaEntrateBiglietto(int index) {
  switch (index) {
    case 0:
      bigliettoView->setTitleSearch("Utente");
      for (auto it = model->getListUtenti().cbegin();
           it != model->getListUtenti().cend(); ++it) {
        bigliettoView->addEntrataToLista(
            QString::fromStdString((*it)->toString()),
            QString::fromStdString((*it)->getCodFisc()));
      }
      break;
    case 1:
      bigliettoView->setTitleSearch("Abbonamento");
      for (auto it = model->getListEntrate().cbegin();
           it != model->getListEntrate().cend(); ++it) {
        try {
          Abbonamento &dumb = dynamic_cast<Abbonamento &>(**it);
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

  if (pathJsonAbbonamenti == "") loadAbbonamenti();
  loadAbbonamentiInAdmin();

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
  if (pathJsonFamiglie == "") loadFamilies();
  if (pathJsonEntrata == "") loadEntrate();
  if (pathJsonAbbonamenti == "") loadAbbonamenti();

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

void Controller::loadAbbonamentiSlot() { loadAbbonamenti(true); }

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

  // aggiunta di array vuoto in json posti
  QFile filePosti(pathJsonPosti);
  if (!filePosti.open(QIODevice::ReadWrite)) {
    openError(QString("File open error: Read"));
  }

  QJsonDocument docPosti;
  QJsonArray *arrayVuoto = new QJsonArray;
  postiObj.insert(admin->getNomeSala(), *arrayVuoto);
  if (arrayVuoto) {
    delete arrayVuoto;
  }
  docPosti.setObject(postiObj);
  filePosti.write(docPosti.toJson());
  filePosti.close();
}

void Controller::newPostoOccupato() {
  QFile file(pathJsonPosti);
  if (!file.open(QIODevice::ReadWrite)) {
    openError(QString("File open error: Read"));
  }
  QJsonDocument doc;
  QJsonArray *array = new QJsonArray;
  auto it = postiObj.find(bigliettoView->getNomeSala());
  *array = it.value().toArray();
  array->append(
      bigliettoView->getCurrentColumn() +
      (bigliettoView->getCurrentRow() * bigliettoView->getColonneMax()));

  postiObj.insert(bigliettoView->getNomeSala(), *array);

  doc.setObject(postiObj);
  file.write(doc.toJson());
  file.close();
}

void Controller::setPostiOccupati() {
  QString s = bigliettoView->getNomeSala();
  auto it = postiObj.find(s);
  QJsonArray *array = new QJsonArray;
  *array = it.value().toArray();
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
    qDebug() << "abbonamento";
  }
}

void Controller::showSala() {
  QString s = bigliettoView->getSelectedFilm();
  QString f = filmObj.find(s).value().toString();
  unsigned int rows = 0, columns = 0;
  for (auto it = model->getListSale().cbegin();
       it != model->getListSale().cend(); ++it) {
    if (QString::fromStdString((**it).getNomesala()) == f) {
      rows = (**it).getRighe();
      columns = (**it).getColonne();
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

  QJsonArray arrayb = vb.toArray();

  QJsonArray arraya = va.toArray();

  if (bigliettoView->getTipologia() == "Biglietto") {
    QString cf = bigliettoView->getSelectName();
    for (auto it = model->getListUtenti().cbegin();
         it != model->getListUtenti().cend(); ++it) {
      if (cf == QString::fromStdString((**it).getCodFisc())) {
        QJsonObject newUser;
        newUser.insert("name", QString::fromStdString((**it).getName()));
        newUser.insert("surname", QString::fromStdString((**it).getSurname()));
        newUser.insert("CF", QString::fromStdString((**it).getCodFisc()));
        newUser.insert("age", QString::number((**it).getAge()));
        newUser.insert("tel.Num",
                       QString::fromStdString((**it).getPhoneNumber()));

        arrayb.push_back(newUser);

        QDate *d = new QDate;
        Data *date = new Data(d->currentDate().year(), d->currentDate().month(),
                              d->currentDate().day());
        bool riduzione = false;
        if ((**it).getAge() < 14) riduzione = true;
        Biglietto *b = new Biglietto(
            std::to_string(++codUt), date, (**it).getCodFisc(), 7.5, riduzione,
            bigliettoView->getSelectedFilm().toStdString());

        model->addEntrata(b);
      }
    }
  }

  if (bigliettoView->getTipologia() == "Abbonamento") {
    QString cod = bigliettoView->getSelectName();
    for (auto it = model->getListAbbonamenti().cbegin();
         it != model->getListAbbonamenti().cend(); ++it) {
      if (cod == QString::fromStdString((**it).getUtente())) {
        Abbonamento *ab = dynamic_cast<Abbonamento *>(&(**it));

        AbbonamentoFamigliare *abf = dynamic_cast<AbbonamentoFamigliare *>(ab);
        if (abf) {
          QDate *d = new QDate;
          QString date = d->currentDate().toString();

          QJsonObject newAbbonamento;
          newAbbonamento.insert("Tipo", "Abbonamento Famigliare");
          newAbbonamento.insert("Data", date);
          newAbbonamento.insert("Utente",
                                QString::fromStdString((**it).getUtente()));
          newAbbonamento.insert("Codice",
                                QString::fromStdString((**it).getCodice()));
          newAbbonamento.insert("Famiglia",
                                QString::fromStdString(abf->getFamiglia()));
          newAbbonamento.insert("Entrate_rimaste", ((**it).getEntrate() - 1));

          arraya.push_back(newAbbonamento);
          model->addEntrata(&(**it));

          //--------------------------------------------------------------------------------------

          QFile updateFile(pathJsonAbbonamenti);
          if (!updateFile.open(QIODevice::ReadOnly)) {
            openError(QString("File open error: Read"));
          }

          QJsonDocument jsonOrg1 =
              QJsonDocument::fromJson(updateFile.readAll());
          updateFile.close();

          QJsonValue v1 = jsonOrg1.object().value(QString("Abbonamenti"));

          QJsonObject object = v1.toObject();

          QJsonObject updateAbbonamento;
          updateAbbonamento.insert("Tipo", "Abbonamento");
          updateAbbonamento.insert(
              "Data", QString::fromStdString((**it).getData()->ToString()));
          updateAbbonamento.insert("Utente",
                                   QString::fromStdString((**it).getUtente()));
          updateAbbonamento.insert("Codice",
                                   QString::fromStdString((**it).getCodice()));
          updateAbbonamento.insert("Famiglia",
                                   QString::fromStdString(abf->getFamiglia()));
          updateAbbonamento.insert("Entrate_rimaste",
                                   ((**it).getEntrate() - 1));

          object.insert(QString::fromStdString((**it).getCodice()),
                        updateAbbonamento);

          QJsonObject obj1;
          obj1.insert("Abbonamenti", object);

          QJsonDocument doc1(obj1);

          if (!updateFile.open(QIODevice::WriteOnly)) {
            openError(QString("File open error: Write"));
          }

          updateFile.write(doc1.toJson());
          updateFile.close();

          abf->removeOneEntrata();

        } else {
          QDate *d = new QDate;
          QString date = d->currentDate().toString();

          QJsonObject newAbbonamento;
          newAbbonamento.insert("Tipo", "Abbonamento");
          newAbbonamento.insert("Data", date);
          newAbbonamento.insert("Utente",
                                QString::fromStdString((**it).getUtente()));
          newAbbonamento.insert("Codice",
                                QString::fromStdString((**it).getCodice()));
          newAbbonamento.insert("Entrate_rimaste", ((**it).getEntrate() - 1));

          arraya.push_back(newAbbonamento);
          model->addEntrata(&(**it));

          // -----------------------------------------------------------------------

          QFile updateFile(pathJsonAbbonamenti);
          if (!updateFile.open(QIODevice::ReadOnly)) {
            openError(QString("File open error: Read"));
          }

          QJsonDocument jsonOrg1 =
              QJsonDocument::fromJson(updateFile.readAll());
          updateFile.close();

          QJsonValue v1 = jsonOrg1.object().value(QString("Abbonamenti"));

          QJsonObject object = v1.toObject();

          QJsonObject updateAbbonamento;
          updateAbbonamento.insert("Tipo", "Abbonamento");
          updateAbbonamento.insert(
              "Data", QString::fromStdString((**it).getData()->ToString()));
          updateAbbonamento.insert("Utente",
                                   QString::fromStdString((**it).getUtente()));
          updateAbbonamento.insert("Codice",
                                   QString::fromStdString((**it).getCodice()));
          updateAbbonamento.insert("Entrate_rimaste",
                                   ((**it).getEntrate() - 1));

          object.insert(QString::fromStdString((**it).getCodice()),
                        updateAbbonamento);

          QJsonObject obj1;
          obj1.insert("Abbonamenti", object);

          QJsonDocument doc1(obj1);

          if (!updateFile.open(QIODevice::WriteOnly)) {
            openError(QString("File open error: Write"));
          }

          updateFile.write(doc1.toJson());
          updateFile.close();

          ab->removeOneEntrata();
        }
      }
    }
  }

  QJsonObject o;
  o.insert("Entrate Singole", arrayb);
  o.insert("Entrate Abbonamento", arraya);
  QJsonObject obj;
  obj.insert("Entrate", o);

  QJsonDocument doc1(obj);

  if (!file.open(QIODevice::WriteOnly)) {
    openError(QString("File open error: Write"));
  }

  file.write(doc1.toJson());
  file.close();

  for (auto i = model->getListEntrate().cbegin();
       i != model->getListEntrate().cend(); ++i) {
    if ((**i).getUtente() == bigliettoView->getSelectName().toStdString()) {
      qDebug() << (**i).getPrezzo();
    }
  }
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
  QVariantList *listAbb = readEntrataAbb(file, canUpdate);
  QVariantList *listBigl = readEntrataBigl(file, canUpdate);
  if (listAbb != nullptr && listBigl != nullptr) {
    popolaVectorEntrate(*listAbb, *listBigl);
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

void Controller::loadAbbonamenti(bool canUpdate) {
  QFile file;
  QVariantMap map = *readAbbonamenti(file, canUpdate);
  popolaVectorAbbonamenti((map));

  view->showLayoutSetup();

  QFileInfo info(file.fileName());
  view->setLabelPathEntrata(info.fileName());
  qDebug() << codAbb;
}

QVariantList *Controller::readUtenti(QFile &file, bool canUpdate) {
  bool t = false;
  while (!t) {
    if (pathJsonUsers == "" || canUpdate) {
      pathJsonUsers = QFileDialog::getOpenFileName(
          view, tr("Carica json Utenti"), "/home/student/QTheater/json",
          tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
    }
    if (pathJsonUsers.contains("users")) {
      t = true;
    }
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
  // bool t=false;
  // while(!t){
  if (pathJsonFamiglie == "" || canUpdate) {
    pathJsonFamiglie = QFileDialog::getOpenFileName(
        view, tr("Carica json Famiglie"), "/home/student/QTheater/json",
        tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }
  //        if(pathJsonUsers.contains("families")) {
  //            t=true;
  //        }
  //}

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

QVariantList *Controller::readEntrataAbb(QFile &file, bool canUpdate) {
  bool t = false;
  while (!t) {
    if (pathJsonEntrata == "" || canUpdate) {
      pathJsonEntrata = QFileDialog::getOpenFileName(
          view, tr("Carica json Entrate"), "/home/student/QTheater/json",
          tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
    }

    if (pathJsonEntrata.contains("entrate")) {
      t = true;
    }
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
        *localList = mainMap["Entrate Abbonamenti"].toList();
        view->changeTitleChooseEntrata("Cambia file json per Entrate");

        return localList;
      } else {
        openError(QString("File vuoto"));
      }
    }
  }

  return nullptr;
}

QVariantList *Controller::readEntrataBigl(QFile &file, bool canUpdate) {
  bool t = false;
  while (!t) {
    if (pathJsonEntrata == "" || canUpdate) {
      pathJsonEntrata = QFileDialog::getOpenFileName(
          view, tr("Carica json Entrate"), "/home/student/QTheater/json",
          tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
    }

    if (pathJsonEntrata.contains("entrate")) {
      t = true;
    }
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
        *localList = mainMap["Entrate Singole"].toList();
        view->changeTitleChooseEntrata("Cambia file json per Entrate");

        return localList;
      } else {
        openError(QString("File vuoto"));
      }
    }
  }

  return nullptr;
}

QJsonObject *Controller::readPosti(QFile &file, bool canUpdate) {
  bool t = false;
  //  while(!t){
  if (pathJsonPosti == "" || canUpdate) {
    pathJsonPosti = QFileDialog::getOpenFileName(
        view, tr("Carica json Posti"), "/home/student/QTheater/json",
        tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }
  //        if(pathJsonUsers.contains("posti")) {
  //            t=true;
  //        }
  //  }
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

        return jObj;

      } else {
        openError(QString("Empty file"));
      }
    }
  }
  return nullptr;
}

QVariantList *Controller::readSale(QFile &file, bool canUpdate) {
  bool t = false;
  //  while(!t){
  if (pathJsonSale == "" || canUpdate) {
    pathJsonSale = QFileDialog::getOpenFileName(
        view, tr("Carica json Sale"), "/home/student/QTheater/json",
        tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
  }
  //        if(pathJsonUsers.contains("sale")) {
  //            t=true;
  //        }
  //  }
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
        view->changeTitleChooseSala("Cambia file json per sale");

        return jObj;

      } else {
        openError(QString("File vuoto"));
      }
    }
  }

  return nullptr;
}

QVariantMap *Controller::readAbbonamenti(QFile &file, bool canUpdate) {
  bool t = false;
  while (!t) {
    if (pathJsonAbbonamenti == "" || canUpdate) {
      pathJsonAbbonamenti = QFileDialog::getOpenFileName(
          view, tr("Carica json Abbonamenti"), "/home/student/QTheater/json",
          tr("json(*.json)"), nullptr, QFileDialog::DontUseNativeDialog);
    }

    if (pathJsonAbbonamenti.contains("abbonamenti")) {
      t = true;
    }
  }

  if (pathJsonAbbonamenti != "") {
    file.setFileName(pathJsonAbbonamenti);

    if (!file.open(QIODevice::ReadOnly)) {
      openError(QString("File open error: Read"));
    } else {
      model->clearVectorAbbonamenti();

      QString json = file.readAll();

      QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));
      if (!doc.isEmpty()) {
        QJsonObject jObj = doc.object();
        QVariantMap *mainMap = new QVariantMap;
        *mainMap = jObj.toVariantMap();
        // QVariantList *localList = new QVariantList();
        //*localList = mainMap["0"].toList() + mainMap["1"].toList();
        view->changeTitleChooseAbbonamenti("Cambia file json per Abbonamenti");

        return mainMap;
      } else {
        openError(QString("File vuoto"));
      }
    }
  }

  // return nullptr;
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

void Controller::popolaVectorEntrate(const QVariantList &listAbb,
                                     const QVariantList &listBigl) {
  for (int i = 0; i < listAbb.length(); ++i) {
    QVariantMap map = listAbb[i].toMap();

    QString tipo = map["Tipo"].toString();

    if (tipo == "Abbonamento") {
      if (model->searchCf(map["Utente"].toString().toStdString())) {
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
        model->addEntrata(new AbbonamentoFamigliare(
            new Data(map["Data"].toString().toStdString()),
            map["Utente"].toString().toStdString(),
            map["Famiglia"].toString().toStdString(), 7.5,
            map["Codice"].toString().toStdString(),
            map["Entrate_rimaste"].toInt()));
      }
    }
  }
  for (int i = 0; i < listBigl.length(); ++i) {
    QVariantMap map = listBigl[i].toMap();
    if (model->searchCf(map["Utente"].toString().toStdString())) {
      model->addEntrata(new Biglietto(
          map["Codice"].toString().toStdString(),
          new Data(map["Data"].toString().toStdString()),
          map["Utente"].toString().toStdString(), 7.5,
          map["Riduzione"].toBool(), map["Film"].toString().toStdString()));
    }
  }
}

void Controller::popolaVectorAbbonamenti(const QVariantMap &map) {
  QString tipo;
  for (int i = 0; i < map["Abbonamenti"].toJsonObject().size(); ++i) {
    tipo = map["Abbonamenti"]
               .toJsonObject()
               .value(QString::number(i))
               .toObject()
               .value("Tipo")
               .toString();

    if (tipo == "Abbonamento") {
      auto m = map["Abbonamenti"]
                   .toJsonObject()
                   .value(QString::number(i))
                   .toObject();
      if (model->searchCf(m.value("Utente").toString().toStdString())) {
        if (m.value("Codice").toString().toInt() > codAbb) {
          codAbb = m.value("Codice").toString().toInt();
        }

        model->addAbbonamento(
            new Abbonamento(new Data(m.value("Data").toString().toStdString()),
                            m.value("Utente").toString().toStdString(), 7.5,
                            m.value("Codice").toString().toStdString(),
                            m.value("Entrate_rimaste").toInt()));
      }
    }

    else if (tipo == "Abbonamento_Famigliare") {
      auto mf = map["Abbonamenti"]
                    .toJsonObject()
                    .value(QString::number(i))
                    .toObject();
      if (model->searchCf(mf.value("Utente").toString().toStdString()) &&
          model->searchNameFamiglia(
              mf.value("Famiglia").toString().toStdString())) {
        if (mf.value("Codice").toString().toInt() > codAbb) {
          codAbb = mf.value("Codice").toString().toInt();
        }

        model->addAbbonamento(new AbbonamentoFamigliare(
            new Data(mf.value("Data").toString().toStdString()),
            mf.value("Utente").toString().toStdString(),
            mf.value("Famiglia").toString().toStdString(), 7.5,
            mf.value("Codice").toString().toStdString(),
            mf.value("Entrate_rimaste").toInt()));
      }
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

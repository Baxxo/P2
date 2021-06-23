#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QComboBox>
#include <QFile>
#include <QJsonArray>
#include <QObject>
#include <QString>
#include <QWidget>
#include <QLineEdit>

#include "admin.h"
#include "biglietto_view.h"
#include "client.h"
#include "errordisplay.h"
#include "famiglia_view.h"
#include "mainwindow.h"
#include "model.h"
#include "utente_View.h"

class Controller : public QObject {
  Q_OBJECT
 private:
  Model *model;
  MainWindow *view;
  Admin *admin;
  Client *client;

  //  bool isAdminOpen;
  //  bool isClientOpen;
  //  bool isUtenteOpen;
  //  bool isFamigliaOpen;
  //  bool isBigliettoOpen;

  Utente_View *utente;
  Famiglia_View *famigliaView;
  Biglietto_View *bigliettoView;

  QString pathJsonUsers;
  QString pathJsonFamiglie;
  QString pathJsonEntrata;
  QString pathJsonPosti;
  QString pathJsonFilm;
  QString pathJsonSale;
  QJsonObject *objUtenti;

  QString readFile(const QString &filename);

  QJsonObject filmObj;

  void popolaVectorUtenti(const QVariantList &list);
  void popolaVectorPosti(const QVariantList &list);
  void popolaVectorFamiglie(const QVariantList &list);
  void popolaVectorEntrate(const QVariantList &list);
  void popolaVectorSale(const QVariantList &list);

  QVariantList *readUtenti(QFile &file, bool canUpdate);
  QVariantList *readFamiglie(QFile &file, bool canUpdate);
  QVariantList *readEntrata(QFile &file, bool canUpdate);
  QVariantList *readPosti(QFile &file, bool canUpdate);
  QVariantList *readSale(QFile &file, bool canUpdate);
  QJsonObject *readFilm(QFile &file, bool canUpdate);

  Famiglia *fam;

  void loadUsers(bool canUpdate = false);
  void loadFamilies(bool canUpdate = false);
  void loadEntrateinView(bool canUpdate = false);
  void loadPostiOccupati(bool canUpdate = false);
  void loadSale(bool canUpdate = false);
  void loadFilm(bool canUpdate = false);

 public slots:

  // apertura finestre
  void openAdmin();
  void openClient();
  void openUtente();
  void openFamiglia();
  // void listaUtenti();
  void openBiglietto();

  void searchCF();

  // slot per caricare json
  void loadUsersSlot();
  void loadFamiliesSlot();
  void loadEntrateSlot();
  void loadPostiSlot();
  void loadSaleSlot();
  void loadFilmSlot();

  // slot per Utente_View
  void annullaUtente();
  void salvaUtente();
  void salvaFamiglia();

  //gestione film
  void newFilm();

  void newSala();


  void stpBigl();

  void showSala();

 public:
  explicit Controller(QObject *parent = nullptr, Model *m = nullptr);
  void setView(MainWindow *v);

  ErrorDisplay *err;

  //  bool getIsAdmin() const;
  //  void setIsAdmin(bool value);

  QString getPathJsonUsers() const;
  QString getPathJsonFamiglie() const;
  QString getPathJsonEntrata() const;
  QString getPathJsonPosti() const;
  QString getPathJsonSale() const;
  QString getPathJsonFilm() const;


  void openError(QString message);

  void createFamiglia(Famiglia &f, Utente *u);

  Famiglia *getFam() const;

  bool addUserToFamily(const QString &cf);
  bool removeUserFromFamily(const QString &cf);
};

#endif  // CONTROLLER_H

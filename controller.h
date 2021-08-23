#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QComboBox>
#include <QFile>
#include <QJsonArray>
#include <QObject>
#include <QString>
#include <QWidget>
#include <QMessageBox>

#include "abbonamento_view.h"
#include "admin.h"
#include "biglietto_view.h"
#include "client.h"
#include "errordisplay.h"
#include "famiglia_view.h"
#include "mainwindow.h"
#include "model.h"
#include "qlineeditclickable.h"
#include "utente_View.h"

class Controller : public QObject {
  Q_OBJECT
 private:
  Model *model;
  MainWindow *view;
  Admin *admin;
  Client *client;

  Utente_View *utente;
  Famiglia_View *famigliaView;
  Abbonamento_view *abbonamentoView;
  Biglietto_View *bigliettoView;

  QString pathJsonUsers;
  QString pathJsonFamiglie;
  QString pathJsonEntrata;
  QString pathJsonPosti;
  QString pathJsonFilm;
  QString pathJsonSale;
  QString pathJsonAbbonamenti;

  QJsonObject *objUtenti;

  QJsonObject filmObj;

  QJsonObject postiObj;

  Famiglia *fam;

  Abbonamento *abb;
  int codAbb;

  AbbonamentoFamigliare *abbFam;
  unsigned int codAbbFam;

  unsigned int codBigl;

  ErrorDisplay *err;

  QString readFile(const QString &filename);

  void loadUsers(bool canUpdate = false);
  void loadFamilies(bool canUpdate = false);
  void loadEntrateinView(bool canUpdate = false);

  void loadEntrate(bool canUpdate = false);
  void loadPostiOccupati(bool canUpdate = false);
  void loadSale(bool canUpdate = false);
  void loadFilm(bool canUpdate = false);
  void loadAbbonamenti(bool canUpdate = false);

  QVariantList *readUtenti(QFile &file, bool canUpdate);
  QVariantList *readFamiglie(QFile &file, bool canUpdate);
  QVariantList *readEntrata(QFile &file, bool canUpdate);
  QJsonObject *readPosti(QFile &file, bool canUpdate);
  QVariantList *readSale(QFile &file, bool canUpdate);
  QJsonObject *readFilm(QFile &file, bool canUpdate);
  QVariantMap *readAbbonamenti(QFile &file, bool canUpdate);

  void popolaVectorUtenti(const QVariantList &list);
  void popolaVectorFamiglie(const QVariantList &list);
  void popolaVectorEntrate(const QVariantList &list);
  void popolaVectorAbbonamenti(const QVariantMap &map);
  void popolaVectorSale(const QVariantList &list);

 public slots:

  // apertura finestre
  void openAdmin();
  void openClient();
  void openUtente();
  void openFamiglia();
  void openAbbonamento();
  void openBiglietto();

  void searchCF();

  // slot per caricare json
  void loadUsersSlot();
  void loadFamiliesSlot();
  void loadEntrateSlot();
  void loadPostiSlot();
  void loadSaleSlot();
  void loadFilmSlot();
  void loadAbbonamentiSlot();

  // slot per Utente_View
  void annullaUtente();
  void salvaUtente();
  void salvaFamiglia();
  // gestione film
  void newFilm();

  void newSala();

  // void setSala();
  void newPostoOccupato();
  void setPostiOccupati();

  void stpBigl();

  void showSala();

  void buyBiglietto();

 public:
  explicit Controller(QObject *parent = nullptr, Model *m = nullptr);
  void setView(MainWindow *v);

  //  bool getIsAdmin() const;
  //  void setIsAdmin(bool value);

  QString getPathJsonUsers() const;
  QString getPathJsonFamiglie() const;
  QString getPathJsonEntrata() const;
  QString getPathJsonPosti() const;
  QString getPathJsonSale() const;
  QString getPathJsonFilm() const;
  QString getPathJsonAbbonamenti() const;

  bool removeAbbonamento(const QString &cod);

  void openError(const QString &message);

  void createFamiglia(Famiglia &f, Utente *u);

  Famiglia *getFam() const;

  bool addUserToFamily(const QString &cf);
  bool removeUserFromFamily(const QString &cf);

  bool createAbbonamento(const QString &cf);
  bool createAbbonamentoFamigliare(const QString &name, const QString &cf);

  void loadUtentiInAdmin();
  void loadFamiglieInAdmin();
  void loadEntrateInAdmin();
  void loadSaleInAdmin();
  void loadFilmInAdmin();
  void loadAbbonamentiInAdmin();
  void loadFilmInBigliettoview();

};

#endif  // CONTROLLER_H

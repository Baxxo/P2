#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QComboBox>
#include <QFile>
#include <QJsonArray>
#include <QMessageBox>
#include <QObject>
#include <QString>
#include <QWidget>

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

  QString regola;

  QJsonObject *objUtenti;

  QJsonObject filmObj;

  QJsonObject postiObj;

  Famiglia *fam;

  Abbonamento *abb;
  int cod;

  AbbonamentoFamigliare *abbFam;

  unsigned int codBigl, rows, columns, colonneMax;

  QString nameSala;

  ErrorDisplay *err;

  QString readFile(const QString &filename);

  void loadUsers(bool canUpdate = false);
  void loadFamilies(bool canUpdate = false);
  void loadEntrateinView(bool canUpdate = false);

  void loadEntrate(bool canUpdate = false);
  void loadPostiOccupati(bool canUpdate = false);
  void loadSale(bool canUpdate = false);
  void loadFilm(bool canUpdate = false);

  QVariantList *readUtenti(QFile &file, bool canUpdate);
  QVariantList *readFamiglie(QFile &file, bool canUpdate);
  QVariantMap *readEntrata(QFile &file, bool canUpdate);
  QJsonObject *readPosti(QFile &file, bool canUpdate);
  QVariantList *readSale(QFile &file, bool canUpdate);
  QJsonObject *readFilm(QFile &file, bool canUpdate);

  void popolaVectorUtenti(const QVariantList &list);
  void popolaVectorFamiglie(const QVariantList &list);
  void popolaVectorEntrate(const QVariantMap &map);
  void popolaVectorSale(const QVariantList &list);

  void removeAbbonamentoFromJson(const QString &cod);

 public slots:

  // apertura finestre
  void openAdmin();
  void openClient();
  void openUtente();
  void openFamiglia();
  void openAbbonamento();
  void openBiglietto();

  void hideAdmin();

  void searchCF();

  // slot per caricare json
  void loadUsersSlot();
  void loadFamiliesSlot();
  void loadEntrateSlot();
  void loadPostiSlot();
  void loadSaleSlot();
  void loadFilmSlot();

  // slot per Utente_View
  void salvaUtente();
  void salvaFamiglia();
  // gestione film
  void newFilm();

  void newSala();

  void newPostoOccupato();
  void setPostiOccupati();

  void stpBigl();

  void showSala();

  void buyBiglietto();

  void setRegola(const QString &s);

 public:
  explicit Controller(QObject *parent = nullptr, Model *m = nullptr);
  void setView(MainWindow *v);

  QString getPathJsonUsers() const;
  QString getPathJsonFamiglie() const;
  QString getPathJsonEntrata() const;
  QString getPathJsonPosti() const;
  QString getPathJsonSale() const;
  QString getPathJsonFilm() const;

  bool removeAbbonamento(const QString &cod);

  void openError(const QString &message);

  void createFamiglia(Famiglia &f, Utente *u);
  void showPrezzo(const EntrataFilm *e);

  Famiglia *getFam() const;

  bool addUserToFamily(const QString &cf);
  bool removeUserFromFamily(const QString &cf);

  bool createAbbonamento(const QString &cf);
  bool createAbbonamentoFamigliare(const QString &name, const QString &cf);

  void loadUtentiInAdmin();
  void addUteneAdmin(const QString &s);

  void loadFamiglieInAdmin();
  void loadEntrateInAdmin();
  void loadSaleInAdmin();
  void loadFilmInAdmin();
  void loadFilmInBigliettoview();

  void popolaEntrateBiglietto(int index);
  unsigned int getColonneMax() const;
  QString getNameSala() const;

  void closeClientWindows();
  void closeAll();
};

#endif  // CONTROLLER_H

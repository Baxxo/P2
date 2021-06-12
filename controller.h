#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QFile>
#include <QJsonArray>
#include <QComboBox>
#include <QString>
#include <QWidget>

#include "mainwindow.h"
#include "admin.h"
#include "client.h"
#include "utente_View.h"
#include "famiglia_view.h"
#include "model.h"
#include "errordisplay.h"
#include "biglietto_view.h"

class Controller : public QObject
{
    Q_OBJECT
private:
    Model* model;
    MainWindow* view;
    Admin* admin;
    Client* client;

    bool isAdminOpen;
    bool isClientOpen;
    bool isUtenteOpen;
    bool isFamigliaOpen;
    bool isBigliettoOpen;

    Utente_View* utente;
    Famiglia_View* famigliaView;
    Biglietto_View* bigliettoView;

    QString pathJsonUsers;
    QString pathJsonFamiglie;
    QString pathJsonEntrata;
    QString pathjsonPosti;
    QString pathJsonFilm;
    QJsonObject* objUtenti;

    QString readFile(const QString &filename);

    void popolaVectorUtenti(const QVariantList &list);
    void popolaVectorPosti(const QVariantList &list);
    void popolaVectorFamiglie(const QVariantList &list);

    QVariantList *readUtenti(QFile &file, bool update = false);
    QVariantList *readFamiglie(QFile &file, bool update = false);
    QVariantList *readEntrata(QFile &file, bool update = false);
    QVariantList *readPosti(QFile &file);
    QVariantList *readFilm(QFile &file);
    Famiglia* fam;

public slots:

    //apertura finestre
    void openAdmin();
    void openClient();
    void openUtente();
    void openFamiglia();
    void listaUtenti();
    void openBiglietto();
    void searchCF();

    void loadUsersinView();
    void loadFamiliesinView();
    void loadEntrateinView();
    void loadPostiOccupati();
    void loadFilm();

    //slot per Utente_View
    void annullaUtente();
    void salvaUtente();
    void salvaFamiglia();

    void stpBigl();

    void showSala();





public:

    explicit Controller(QObject *parent = nullptr, Model* m = nullptr);
    void setView(MainWindow* v);

    ErrorDisplay* err;

    bool getIsAdmin() const;
    void setIsAdmin(bool value);

    QString getPathJsonUsers() const;
    QString getPathJsonFamiglie() const;
    QString getPathJsonEntrata() const;
    QString getPathJsonPosti() const;
    QString getPathJsonFilm() const;

    void openError(QString message);

    void createFamiglia(Famiglia& f, Utente* u);

    Famiglia *getFam() const;

    bool addUserToFamily(const QString &cf);
    bool removeUserFromFamily(const QString &cf);

};

#endif // CONTROLLER_H

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
    QVariantList *readUtenti(QFile &file);
    QVariantList *readPosti(QFile &file);
    QVariantList *readFilm(QFile &file);

public slots:

    //apertura finestre
    void openAdmin();
    void openClient();
    void openUtente();
    void openFamiglia();
    void listaUtenti();
    void openBiglietto();

    void readFimiglie();
    void readEntrata();
    void loadUsersinView();
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

};

#endif // CONTROLLER_H

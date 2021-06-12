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

    Utente_View* utente;
    Famiglia_View* famigliaView;

    QString pathJsonUsers;
    QString pathJsonFamiglie;
    QString pathJsonEntrata;
    QJsonObject* objUtenti;

    QString readFile(const QString &filename);

    void popolaVectorUtenti(const QVariantList &list);
    void popolaVectorFamiglie(const QVariantList &list);

    QVariantList *readUtenti(QFile &file, bool update = false);
    QVariantList *readFimiglie(QFile &file, bool update = false);
    QVariantList *readEntrata(QFile &file, bool update = false);
    Famiglia* fam;

public slots:

    //apertura finestre
    void openAdmin();
    void openClient();
    void openUtente();
    void openFamiglia();
    void searchCF();

    void loadUsersinView();
    void loadFamiliesinView();
    void loadEntrateinView();

    //slot per Utente_View
    void annullaUtente();
    void salvaUtente();
    void salvaFamiglia();

public:

    explicit Controller(QObject *parent = nullptr, Model* m = nullptr);
    void setView(MainWindow* v);

    ErrorDisplay* err;

    bool getIsAdmin() const;
    void setIsAdmin(bool value);

    QString getPathJsonUsers() const;
    QString getPathJsonFamiglie() const;
    QString getPathJsonEntrata() const;

    void openError(QString message);

    void createFamiglia(Famiglia& f, Utente* u);

    Famiglia *getFam() const;

    bool addUserToFamily(const QString &cf);
    bool removeUserFromFamily(const QString &cf);
};

#endif // CONTROLLER_H

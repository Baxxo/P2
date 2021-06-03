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

    bool isAdmin;
    bool isClient;
    bool isUtente;
    bool isFamiglia;

    Utente_View* utente;
    Famiglia_View* famiglia;

    QString pathJsonUsers;
    QJsonObject* objUtenti;

    void loadUsersinView() const;

    QString readFile(const QString &filename);

    void openError(QString message);

private slots:

    //apertura finestre
    void openAdmin();
    void openClient();
    void openUtente();
    void openFamiglia();
    void listaUtenti();

    void readUtenti();
    void readFimiglie();
    void readEntrata();

    //slot per Utente_View
    void annullaUtente();
    void salvaUtente();

public:

    explicit Controller(QObject *parent = nullptr, Model* m = nullptr);
    void setView(MainWindow* v);

    QString getPathJson() const;

    ErrorDisplay* err;

    bool getIsAdmin() const;
    void setIsAdmin(bool value);

signals:

};

#endif // CONTROLLER_H

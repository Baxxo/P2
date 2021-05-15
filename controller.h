#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <Mainwindow.h>
#include <admin.h>
#include <client.h>
#include <Utente_View.h>
#include <QFile>
#include <QJsonArray>


class Controller : public QObject
{
    Q_OBJECT
private:
    MainWindow* view;
    Admin* admin;
    Client* client;
    Utente_View* utente;
    bool isAdmin;
    bool isClient;
    bool isUtente;
    QJsonArray* arrayUtenti;

public:

    explicit Controller(QObject *parent = nullptr);
    void setView(MainWindow* v);


private slots:

    //apertura finestre
    void openAdmin();
    void openClient();
    void openUtente();

    //slot per Utente_View
    void annullaUtente();
    void salvaUtente();

signals:

};

#endif // CONTROLLER_H

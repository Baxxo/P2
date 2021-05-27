#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <Mainwindow.h>
#include <admin.h>
#include <client.h>
#include <Utente_View.h>
#include <QFile>
#include <QJsonArray>
#include <famiglia_view.h>
#include <QComboBox>



class Controller : public QObject
{
    Q_OBJECT
private:
    MainWindow* view;
    Admin* admin;
    Client* client;
    Utente_View* utente;
    Famiglia_View* famiglia;
    bool isAdmin;
    bool isClient;
    bool isUtente;
    bool isFamiglia;
    QJsonObject* objUtenti;

public:

    explicit Controller(QObject *parent = nullptr);
    void setView(MainWindow* v);
    void readUtenti();


private slots:

    //apertura finestre
    void openAdmin();
    void openClient();
    void openUtente();
    void openFamiglia();
    void listaUtenti();

    //slot per Utente_View
    void annullaUtente();
    void salvaUtente();

signals:

};

#endif // CONTROLLER_H

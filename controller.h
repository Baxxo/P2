#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <mainwindow.h>
#include <admin.h>
#include <client.h>
#include <utente_View.h>
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
    QJsonObject* objFamiglie;
    QString pathJsonUtenti;
    QString pathJsonFamiglie;

public:

    explicit Controller(QObject *parent = nullptr);
    void setView(MainWindow* v);
    void readUtenti();
    void readFamiglie();


    QString getPathJsonUtenti() const;

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

    //slot per famiglia_view
    void salvaFamiglia();

signals:

};

#endif // CONTROLLER_H

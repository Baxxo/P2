#ifndef FAMIGLIA_VIEW_H
#define FAMIGLIA_VIEW_H
#include <QWidget>
#include <QListView>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "qlineeditclickable.h"
#include "qlabelcf.h"
#include "utente_View.h"

using std::string;

class Famiglia_View:public QWidget
{
    Q_OBJECT
private:

    QLineEditClickable* familyName;
    QListWidget* listaUtenti;
    QLineEditClickable* search;

    QVBoxLayout* menuLayout;
    QVBoxLayout* btnLayout;
    Controller* controller;
    QPushButton* aggiorna;
    QPushButton* saveFamily;
    QGridLayout* mainlayout;
    QWidget* widget;

    QString read();

private slots:
    void signaltest();
    void resizeMe();

    void cleanTextFamily();
    void cleanTextSearch();

public:
    Famiglia_View(Controller* c, QWidget *parent=nullptr);
    void addUtenteToLista(const QString &text, const QString &cf);
    //void showMenu();
    void setStyle();
    QString getItem(int i);
    QString getSearch();
    int getListSize();
    QString getFamilyName();

    void clearList();


};

#endif // FAMIGLIA_VIEW_H

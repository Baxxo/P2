#ifndef FAMIGLIA_VIEW_H
#define FAMIGLIA_VIEW_H
#include <QWidget>
#include <QListView>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include "utente_View.h"
using std::string;

class Famiglia_View:public QWidget
{
    Q_OBJECT
private:
    QListWidget* listaFamily;
    QLineEdit* search;
    QLineEdit* familyName;
    QVBoxLayout* menuLayout;
    QVBoxLayout* btnLayout;
    Controller* controller;
    QPushButton* aggiorna;
    QPushButton* saveFamily;
    QGridLayout* mainlayout;
    QWidget* widget;
    QDesktopWidget* desktop;

    QString read();

private slots:
    void signaltest();
public:
    Famiglia_View(Controller* c, QWidget *parent=nullptr);
    void addLista(QString m);
    //void showMenu();
    void setStyle();
    QString getItem(int i);
    QString getSearch();
    int getListSize();
    QString getFamilyName();

};

#endif // FAMIGLIA_VIEW_H

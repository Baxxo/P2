#ifndef FAMIGLIA_VIEW_H
#define FAMIGLIA_VIEW_H
#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "utente_View.h"
using std::string;

class Famiglia_View:public QWidget
{
    Q_OBJECT
private:
    QComboBox* menu;
    QComboBox* listaFamily;
    QVBoxLayout* menuLayout;
    QVBoxLayout* btnLayout;
    Controller* controller;
    QPushButton* aggiorna;
    QGridLayout* mainlayout;
    QWidget* widget;
    QDesktopWidget* desktop;

    QString read();

private slots:
    void signaltest();
public:
    Famiglia_View(Controller* c, QWidget *parent=nullptr);
    void setMenu(QComboBox* m);
    void showMenu();
    void setStyle();

};

#endif // FAMIGLIA_VIEW_H

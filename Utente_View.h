#ifndef UTENTE_VIEW_H
#define UTENTE_VIEW_H
#include <QWidget>
//#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QFile>
#include <QLabel>
#include <QDesktopWidget>
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include "Mainwindow.h"

using std::cout;

class Utente_View:public QWidget
{
    Q_OBJECT

private:
    QWidget* widget;
    QGridLayout* mainlayout;
    QVBoxLayout* btnLayout;
    QVBoxLayout* lineLayout;
    QPushButton* confermaBtn;
    QPushButton* annullaBtn;
    QLineEdit* name;
    QLineEdit* CF;
    QLineEdit* age;
    QLineEdit* numtel;
    QDesktopWidget* desktop;
    Controller* controller;

public:
    Utente_View(Controller *c, QWidget *parent=nullptr);
    void setStyle();
    QString getName();
    QString getCF();
    QString getAge();
    QString getNumTel();




};

#endif // UTENTE_VIEW_H
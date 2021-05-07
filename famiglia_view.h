#ifndef FAMIGLIA_VIEW_H
#define FAMIGLIA_VIEW_H
#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Utente_View.h"
using std::string;

class Famiglia_View:public QWidget
{
    Q_OBJECT
private:
    QComboBox* menu;
    QVBoxLayout* mainlayout;

private slots:
    QString read();
public:
    Famiglia_View(QWidget *parent=nullptr);
};

#endif // FAMIGLIA_VIEW_H

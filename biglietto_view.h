#ifndef BIGLIETTO_VIEW_H
#define BIGLIETTO_VIEW_H

#include <QWidget>
#include <QComboBox>
#include <QDebug>
#include <QListWidget>
#include <QTableWidget>

#include "mainwindow.h"

class Biglietto_View : public QWidget
{
    Q_OBJECT
private:
    Controller* controller;
    int prezzo;
    QString film;
    QComboBox* tipologia;
    QVBoxLayout* layoutTipologia;
    QWidget* mainWidget;
    QWidget* widgetSing;
    QWidget* salaWidget;
    QVBoxLayout* compraLayout;
    QGridLayout* mainLayout;
    QPushButton* compraBiglietto;
    QListWidget* listaFilm;
    QPushButton* tipologiaBtn;
    QVBoxLayout* utenteBigl;
    QLineEdit* search;
    QPushButton* searchBtn;
    QVBoxLayout* salaLayout;
    QPushButton* selectSeat;
    QTableWidget* posti;
public:
    explicit Biglietto_View(Controller* c, QWidget *parent = nullptr);
    void setStyle();
    QString getSearch();
    QString getTipologia();
    void getSalaView();

private slots:
    void showSearch();

};

#endif // BIGLIETTO_VIEW_H

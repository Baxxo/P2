#ifndef BIGLIETTO_VIEW_H
#define BIGLIETTO_VIEW_H

#include <QComboBox>
#include <QDebug>
#include <QListWidget>
#include <QTableWidget>
#include <QWidget>

#include "mainwindow.h"

class Biglietto_View : public QWidget {
  Q_OBJECT
private:
  Controller *controller;
  int prezzo;
  QString film;
  QComboBox *tipologia;
  QVBoxLayout *layoutTipologia;
  QWidget *mainWidget;
  QWidget *widgetSing;
  QWidget *salaWidget;
  QVBoxLayout *compraLayout;
  QGridLayout *mainLayout;
  QPushButton *compraBiglietto;
  QListWidget *listaFilm;
  QPushButton *tipologiaBtn;
  QVBoxLayout *utenteBigl;
  QLineEdit *search;
  QPushButton *searchBtn;
  QVBoxLayout *salaLayout;
  QTableWidget *posti;
  QLabel* nomeSala;
  QLabel* colonneMax;
  
  unsigned int *postiOccupati;

public:
  explicit Biglietto_View(Controller *c, QWidget *parent = nullptr);
  void setStyle();
  QString getSearch();
  QString getTipologia();
  void getSalaView();
  void addFilminList(QString s);
  int getCurrentColumn();
  int getCurrentRow();
  QString getNomeSala();
  QString getSelectedFilm();
  int getColonneMax();
  void setPostoOccupato(int r, int c);
  void createSalaView(int r, int c, QString f);

private slots:
  void showSearch();
  void resizeMe();

};

#endif // BIGLIETTO_VIEW_H

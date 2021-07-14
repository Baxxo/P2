#ifndef BIGLIETTO_VIEW_H
#define BIGLIETTO_VIEW_H

#include <QComboBox>
#include <QListWidget>
#include <QTableWidget>
#include <QWidget>

#include <QDebug>

#include <qlineeditclickable.h>
#include "mainwindow.h"

class Biglietto_View : public QWidget {
  Q_OBJECT
 private:
  Controller *controller;
  int prezzo;
  QString film;

  QGridLayout *mainLayout;

  QLabel *labelTipo;
  QComboBox *tipologia;
  QPushButton *tipologiaBtn;
  QVBoxLayout *layoutTipologia;

  QLabel *searchUtility;
  QLineEditClickable *search;
  QPushButton *searchBtn;
  QVBoxLayout *utenteBigl;
  QWidget *widgetSearchCf;

  QLabel *labelListaFilm;
  QListWidget *listaFilm;
  QVBoxLayout *compraLayout;

  QPushButton *selectSeat;
  QVBoxLayout *salaLayout;
  QWidget *salaWidget;

  QTableWidget *posti;
  QLabel *nomeSala;
  QLabel *colonneMax;

  QPushButton *compraBiglietto;

  unsigned int *postiOccupati;

  QWidget *mainWidget;
  QWidget *widgetSing;

 private slots:
  void showSearch();
  void showSalaView();

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

 public slots:
  void resizeSala();
  void resizeMe();

  void setUtilitySearchText(const QString &s);
};

#endif  // BIGLIETTO_VIEW_H

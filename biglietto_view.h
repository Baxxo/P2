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

  QPushButton *compraBiglietto;

 private slots:
  void showSearch();

 public:
  explicit Biglietto_View(Controller *c, QWidget *parent = nullptr);
  void setStyle();
  QString getSearch();
  QString getTipologia();
  void showSalaView();

  void setUtilitySearchText(const QString &s);

 public slots:
  void resizeSala();
  void resizeMe();
};

#endif  // BIGLIETTO_VIEW_H

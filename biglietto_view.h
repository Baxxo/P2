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
  QLabel *labelTipo;
  QComboBox *tipologia;
  QVBoxLayout *layoutTipologia;
  QWidget *mainWidget;
  QWidget *widgetSing;
  QWidget *salaWidget;
  QVBoxLayout *compraLayout;
  QGridLayout *mainLayout;
  QPushButton *compraBiglietto;
  QLabel *labelListaFilm;
  QListWidget *listaFilm;
  QPushButton *tipologiaBtn;
  QVBoxLayout *utenteBigl;
  QLabel *searchUtility;
  QLineEditClickable *search;
  QPushButton *searchBtn;
  QVBoxLayout *salaLayout;
  QPushButton *selectSeat;
  QTableWidget *posti;

 public:
  explicit Biglietto_View(Controller *c, QWidget *parent = nullptr);
  void setStyle();
  QString getSearch();
  QString getTipologia();
  void getSalaView();

  void setUtilitySearchText(const QString &s);

 private slots:
  void showSearch();
  void resizeMe();
};

#endif  // BIGLIETTO_VIEW_H

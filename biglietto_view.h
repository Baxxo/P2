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
  QListWidget *listaSearch;
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

  QString selectName;

  QString titleSearch;

  bool isAlreadySelectdSearch;

  QString selectFromSearch;

 private slots:
  void showSearch();
  void showSalaView();

  void getNameSelect(QListWidgetItem *item);

  void popolaLista(int index);

  void selectFromListSearch(QListWidgetItem *item);

 public:
  explicit Biglietto_View(Controller *c, QWidget *parent = nullptr);
  void setStyle();
  QString getSearch();
  QString getTipologia();
  void getSalaView();

  void addFilminList(const QString &s);
  void addEntrataToLista(const QString &text, const QString &cod);

  int getCurrentColumn();
  int getCurrentRow();
  QString getNomeSala();
  QString getSelectedFilm();
  int getColonneMax();
  void setPostoOccupato(unsigned int r, unsigned int c, QString regola);
  void createSalaView(unsigned int r, unsigned int c, const QString &f);

  void clearListFilm();

  QString getSelectName() const;
  void setTitleSearch(const QString &t);

  QString getSelectFromSearch() const;

 public slots:
  void resizeSala();
  void resizeMe();

  void setUtilitySearchText(const QString &s);
};

#endif  // BIGLIETTO_VIEW_H

#ifndef BIGLIETTO_VIEW_H
#define BIGLIETTO_VIEW_H

#include <QComboBox>
#include <QHeaderView>
#include <QListWidget>
#include <QTableWidget>
#include <QWidget>

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

  QLabel *selectedItemSearch;
  QLabel *searchUtility;
  QListWidget *listaSearch;
  QVBoxLayout *utenteBigl;
  QWidget *widgetSearchCf;

  QLabel *labelListaFilm;
  QListWidget *listaFilm;
  QVBoxLayout *compraLayout;

  QVBoxLayout *salaLayout;
  QWidget *salaWidget;

  QTableWidget *posti;

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
  QString getTipologia();
  void getSalaView();

  void addFilminList(const QString &s);
  void addEntrataToLista(const QString &text, const QString &cod);

  int getCurrentColumn();
  int getCurrentRow();
  QString getSelectedFilm();
  void setPostoOccupato(unsigned int r, unsigned int c, QString regola);
  void createSalaView(unsigned int r, unsigned int c);

  void clearListFilm();

  QString getSelectName() const;
  void setTitleSearch(const QString &t);

  QString getSelectFromSearch() const;

 public slots:
  void resizeSala();
  void resizeMe();
  void hideSalaView();

  void setUtilitySearchText(const QString &s);
};

#endif  // BIGLIETTO_VIEW_H

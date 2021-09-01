#ifndef FAMIGLIA_VIEW_H
#define FAMIGLIA_VIEW_H
#include <QHBoxLayout>
#include <QListView>
#include <QListWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "qlabelcf.h"
#include "qlineeditclickable.h"
#include "utente_View.h"

using std::string;

class Famiglia_View : public QWidget {
  Q_OBJECT
 private:
  QLineEditClickable *familyName;
  QListWidget *listaUtenti;
  QLineEditClickable *searchEditText;

  QVBoxLayout *menuLayout;
  QVBoxLayout *btnLayout;
  QPushButton *searchBtn;
  QPushButton *saveFamily;
  QGridLayout *mainlayout;
  QWidget *widget;

  QVBoxLayout *layoutListUsers;
  QLabel *labelListaUtenti;
  QLabel *utility;

  Controller *controller;

 private slots:

  void resizeMe();
  void cleanUtilityText();

  void cleanTextFamily();
  void cleanTextSearch();

  void addUtenteToFamiglia(QListWidgetItem *item);

 public:
  Famiglia_View(Controller *c, QWidget *parent = nullptr);

  void addUtenteToLista(const QString &text, const QString &cf);
  void setStyle();
  int getListSize();
  void clearList();

  void selectIndexbyCF(QString cf);

  QString getItem(int i);
  QString getSearch();
  QString getFamilyName();

  QString getCF_SearchText() const;

  void findUser(QString search);

  void setUtilityText(QString txt);
};

#endif  // FAMIGLIA_VIEW_H

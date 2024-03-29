#ifndef ABBONAMENTO_VIEW_H
#define ABBONAMENTO_VIEW_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWidget>

#include "mainwindow.h"
#include "qlabelcf.h"

class Abbonamento_view : public QWidget {
  Q_OBJECT
 private:
  Controller* controller;

  QVBoxLayout* mainLayout;
  QGroupBox* tipoAbbonamento;
  QHBoxLayout* layoutRadio;
  QRadioButton* abbonamento;
  QRadioButton* abbonamentoFamigliare;

  QLabel* utentiLabel;
  QListWidget* listaUtenti;
  QLabel* famiglieLabel;
  QListWidget* listaFamiglie;

  QPushButton* aggiungi;

  QLabel* labelUtility;

  QListWidgetItem* currentUser;
  QListWidgetItem* currentfamily;

  bool isUtente;
  bool alreadySelectedUt;
  bool alreadySelectedFm;

  void setStyle();

  bool addAbbonamentoToController(const QString& cf);
  bool addAbbonamentoFamToController(const QString& name, const QString& cf);

 private slots:

  void showAbbonamento();
  void showAbbFamiglaire();
  void createAbbonamento();

  void resizeMe();

  void clickListUtenti(QListWidgetItem* item);
  void clickListFamiglie(QListWidgetItem* item);

  void clearUtilityText();

 public:
  explicit Abbonamento_view(Controller* c, QWidget* parent = nullptr);

  void addUtente(const QString& s, const QString& cf);
  void addFamiglia(const QString& s, const QString& name);

  void clearListUtenti();
  void clearListFamiglie();
};

#endif  // ABBONAMENTO_VIEW_H

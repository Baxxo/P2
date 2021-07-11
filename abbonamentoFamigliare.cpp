#include "abbonamentoFamigliare.h"
#include <QDebug>

AbbonamentoFamigliare::AbbonamentoFamigliare(Data *d, Utente *u, Famiglia *f,
                                             double p, string c, int e)
    : Abbonamento(d, u, p, c, e), famiglia(f) {
  qDebug() << "costruttore abb fam 1.1"
           << QString::fromStdString(famiglia->getName());
  qDebug() << "costruttore abb f 1.1" << QString::fromStdString(f->getName());

  for (unsigned int i = 0; i < f->getSize(); ++i)
    qDebug() << "f[" << i << "] " << QString::fromStdString(f[i].getCodFisc());
}

AbbonamentoFamigliare::AbbonamentoFamigliare(const AbbonamentoFamigliare &o)
    : Abbonamento(o), famiglia(o.famiglia) {}

AbbonamentoFamigliare::~AbbonamentoFamigliare() {
  qDebug() << "distr abb fam 1";
  if (famiglia != nullptr) {
    qDebug() << "distr abb fam 1.1"
             << QString::fromStdString(famiglia->getName());

    for (unsigned int i = 0; i < famiglia->getSize(); ++i)
      qDebug() << QString::fromStdString(famiglia[i].getCodFisc());

    delete famiglia;

    qDebug() << "distr abb fam 1.2";
  }
  qDebug() << "distr abb fam 2";
}

Famiglia *AbbonamentoFamigliare::getFamiglia() const { return famiglia; }

AbbonamentoFamigliare *AbbonamentoFamigliare::clone() const {
  qDebug() << "clone abb fam";
  return new AbbonamentoFamigliare(*this);
}

double AbbonamentoFamigliare::getPrezzo() const {
  return EntrataFilm::getPrezzo() * getEntrate();
}

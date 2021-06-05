#include "qlabelcf.h"

#include <QVBoxLayout>

#include <QDebug>

QLabelCF::QLabelCF(QLabel *parent, const QString &_cf,QFlag flag) : QLabel(parent->text()), cf(_cf)
{
  setAlignment(flag);
}

QString QLabelCF::getCf() const
{
  return cf;
}

#include "qlabelcf.h"

#include <QVBoxLayout>

#include <QDebug>

QLabelCF::QLabelCF(QLabel *parent, const QString &_cf, QFlag flag, bool s) : QLabel(parent->text()), cf(_cf), select(s)
{
  setAlignment(flag);
}

QString QLabelCF::getCf() const
{
  return cf;
}

bool QLabelCF::isSelected() const
{
  return select;
}

void QLabelCF::setSelect(bool s)
{
  select = s;
}

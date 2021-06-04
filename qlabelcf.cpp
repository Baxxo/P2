#include "qlabelcf.h"

QLabelCF::QLabelCF(QWidget *parent, const QString &_cf): QLabel(parent), cf(_cf)
{

}

QString QLabelCF::getCf() const
{
    return cf;
}

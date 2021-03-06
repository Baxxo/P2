#include "qlabelcf.h"

#include <QVBoxLayout>

QLabelCF::QLabelCF(QLabel *parent, const QString &_cf, QFlag flag, bool s)
    : QLabel(parent->text(), parent, flag), cf(_cf), select(s) {}

QString QLabelCF::getCf() const { return cf; }

bool QLabelCF::isSelected() const { return select; }

void QLabelCF::setSelect(bool s) { select = s; }

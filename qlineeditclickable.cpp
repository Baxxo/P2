#include "qlineeditclickable.h"

QLineEditClickable::QLineEditClickable(QWidget *parent): QLineEdit(parent)
{

}

void QLineEditClickable::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}

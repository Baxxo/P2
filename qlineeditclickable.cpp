#include "qlineeditclickable.h"

QLineEditClickable::QLineEditClickable(QString text, QWidget *parent): QLineEdit(text, parent)
{

}

void QLineEditClickable::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
        emit clicked();
      }
}

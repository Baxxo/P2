#ifndef QLINEEDITCLICKABLE_H
#define QLINEEDITCLICKABLE_H

#include <QLineEdit>
#include <QMouseEvent>


class QLineEditClickable: public QLineEdit
{
    Q_OBJECT
public:
   explicit QLineEditClickable(QString text="", QWidget* parent = Q_NULLPTR);
    ~QLineEditClickable() = default;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // QLINEEDITCLICKABLE_H

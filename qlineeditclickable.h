#ifndef QLINEEDITCLICKABLE_H
#define QLINEEDITCLICKABLE_H

#include <QLineEdit>


class QLineEditClickable: public QLineEdit
{
    Q_OBJECT
public:
   explicit QLineEditClickable(QWidget* parent = Q_NULLPTR);//, Qt::WindowFlags f = Qt::WindowFlags()
    ~QLineEditClickable() = default;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // QLINEEDITCLICKABLE_H

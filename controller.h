#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <Utente_View.h>


class Controller : public QObject
{
    Q_OBJECT
private:
    Utente_View* view;
public:

    explicit Controller(QObject *parent = nullptr);
    void setView(Utente_View*v);

private slots:


signals:

};

#endif // CONTROLLER_H

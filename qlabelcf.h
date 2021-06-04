#ifndef QLABELCF_H
#define QLABELCF_H

#include <QLabel>
#include <QString>

class QLabelCF: public QLabel
{
    Q_OBJECT
public:
    explicit QLabelCF(QWidget* parent = Q_NULLPTR, const QString &_cf = "");
    virtual ~QLabelCF() = default;

    QString getCf() const;

private:
    QString cf;
};

#endif // QLABELCF_H

#ifndef QLABELCF_H
#define QLABELCF_H

#include <QLabel>
#include <QFlag>

class QLabelCF : public QLabel
{
public:
  explicit QLabelCF(QLabel *parent = nullptr, const QString& _cf = "", QFlag flag = Qt::AlignLeft);
  ~QLabelCF() = default;

  QString getCf() const;

private:
  QString cf;

signals:

public slots:
};

#endif // QLABELCF_H

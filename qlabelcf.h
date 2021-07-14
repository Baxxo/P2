#ifndef QLABELCF_H
#define QLABELCF_H

#include <QLabel>
#include <QFlag>

class QLabelCF : public QLabel
{
public:
  explicit QLabelCF(QLabel *parent = nullptr, const QString& _cf = "", QFlag flag = Qt::AlignLeft, bool s = false);
  ~QLabelCF() = default;

  QString getCf() const;

  bool isSelected() const;

  void setSelect(bool s);

private:
  QString cf;
  bool select;

signals:

public slots:
};

#endif // QLABELCF_H

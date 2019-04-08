#ifndef SAMPLE_H
#define SAMPLE_H

#include <QObject>

class Sample : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString getVar READ getVar WRITE setVar NOTIFY varChanged)
public:
  explicit Sample(const QString &var, QObject *parent = nullptr)
      : QObject(parent), mVar(var) {}

  QString getVar() const { return mVar; }
  void setVar(const QString &var) {
    if (mVar == var)
      return;
    mVar = var;
    emit varChanged();
  }
signals:
  void varChanged();

private:
  QString mVar;
};

#endif // SAMPLE_H

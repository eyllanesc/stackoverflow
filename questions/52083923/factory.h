#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>
#include <QVariant>

#include "money.h"

class Factory : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(Factory)

public:
  static Factory *instance() {
    static Factory factory;
    return &factory;
  }

  Q_INVOKABLE QVariant getMoney() {
    return QVariant::fromValue(Money(12345, Currency::getUSD()));
  }

private:
  explicit Factory(QObject *parent = nullptr) : QObject(parent) {}
};

#endif // FACTORY_H

#ifndef CURRENCY_H
#define CURRENCY_H

#include <QObject>

class Currency {
  Q_GADGET

  Q_PROPERTY(QString name READ getName CONSTANT)

public:
  Currency() : name("") {}

  Currency(const Currency &that) = default;
  Currency &operator=(const Currency &that) = default;

  static Currency getUSD() { return Currency("USD"); }

  QString getName() { return this->name; }

private:
  Currency(const QString &name) : name(name) {}
  QString name;
};

Q_DECLARE_METATYPE(Currency)

#endif // CURRENCY_H

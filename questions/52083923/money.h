#ifndef MONEY_H
#define MONEY_H

#include "currency.h"

#include <QObject>

class Money {
  Q_GADGET

  Q_PROPERTY(int amount READ getAmount CONSTANT)
  Q_PROPERTY(Currency currency READ getCurrency CONSTANT)

public:
  Money() : Money(0, Currency()) {}

  Money(int amount, const Currency &currency)
      : amount(amount), currency(currency) {}

  int getAmount() { return this->amount; }

  Currency getCurrency() { return this->currency; }

private:
  int amount;
  Currency currency;
};

#endif // MONEY_H

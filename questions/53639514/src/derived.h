#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"
#include "foomodule_global.h"

class FOOMODULESHARED_EXPORT Derived : public Base {
  Q_OBJECT
public:
  explicit Derived(QObject *parent = nullptr);
  QString doStuff() override;
};

#endif // DERIVED_H

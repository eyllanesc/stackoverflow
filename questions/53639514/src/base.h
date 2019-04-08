#ifndef BASE_H
#define BASE_H

#include "foomodule_global.h"
#include <QObject>

class FOOMODULESHARED_EXPORT Base : public QObject {
  Q_OBJECT
public:
  explicit Base(QObject *parent = nullptr);
  virtual QString doStuff();
};

#endif // BASE_H

#ifndef INTERFACEPLUGIN_H
#define INTERFACEPLUGIN_H

#include "interfaceplugin_global.h"

#include <QObject>

class INTERFACEPLUGINSHARED_EXPORT Interface : public QObject {
  Q_OBJECT
public:
  virtual ~Interface() {}

  // Slot which should cause emission of `name` signal.
  virtual void getName() = 0;

signals:
  // Signal to be emitted in getName()
  void name(QString);
};

#define InterfaceIID "interface"
Q_DECLARE_INTERFACE(Interface, InterfaceIID)

#endif // INTERFACEPLUGIN_H

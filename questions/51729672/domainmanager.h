#ifndef DOMAINMANAGER_H
#define DOMAINMANAGER_H

#include <QDebug>
#include <QObject>

class Control : public QObject {
  Q_OBJECT
public:
  using QObject::QObject;
  ~Control() { qDebug() << "deleting control"; }
};

class DomainManager : public QObject {
  Q_OBJECT
public:
  using QObject::QObject;
  Q_INVOKABLE Control *controlWriter(QString partition) {
    Control *control = new Control;
    control->setObjectName(partition);
    return control;
  }
};

#endif // DOMAINMANAGER_H

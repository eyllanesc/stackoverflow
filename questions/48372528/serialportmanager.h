#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QObject>
#include <QSerialPortInfo>
#include <QVariant>

class SerialPortManager : public QObject {
  Q_OBJECT
public:
  Q_INVOKABLE static QVariant availablePorts() {
    QList<QSerialPortInfo> portsAvailable = QSerialPortInfo::availablePorts();
    QStringList names_PortsAvailable;
    for (const QSerialPortInfo &portInfo : portsAvailable) {
      names_PortsAvailable << portInfo.portName();
    }
    return QVariant::fromValue(names_PortsAvailable);
  }
};

#endif // SERIALPORTMANAGER_H

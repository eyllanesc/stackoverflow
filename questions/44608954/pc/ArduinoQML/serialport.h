#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialPort : public QObject {
  Q_OBJECT
  Q_PROPERTY(double oil_pressure_volt READ get_oil_pressure_volt WRITE
                 set_oil_pressure_volt NOTIFY oil_pressure_volt_Changed)

public:
  SerialPort(QObject *parent = 0);
  ~SerialPort();

  double get_oil_pressure_volt() const;
  void set_oil_pressure_volt(double newValue);

public slots:
  void onReadData();

signals:
  void oil_pressure_volt_Changed(double newValue);

private:
  QSerialPort *arduino;
  static const quint16 arduino_uno_vendor_id = 0x2341;
  static const quint16 arduino_uno_product_id = 0x0001;

  double mOil_pressure_volt;

  QSerialPortInfo portInfo;

  void openDefault();
};

#endif // SERIALPORT_H

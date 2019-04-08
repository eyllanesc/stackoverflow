#include "serialport.h"

#include <QDebug>

SerialPort::SerialPort(QObject *parent) : QObject(parent) {

  arduino = new QSerialPort(this);
  connect(arduino, &QSerialPort::readyRead, this, &SerialPort::onReadData);
  openDefault();
}

SerialPort::~SerialPort() { delete arduino; }

void SerialPort::set_oil_pressure_volt(double newValue) {
  if (mOil_pressure_volt == newValue)
    return;

  mOil_pressure_volt = newValue;
  emit oil_pressure_volt_Changed(mOil_pressure_volt);
}

void SerialPort::onReadData() {
  if (arduino->bytesAvailable() > 0) {

    QByteArray data = arduino->readAll();
    qDebug() << QString(data).trimmed();
    QString value = QString(data).trimmed();
    bool ok;
    double val = value.toDouble(&ok);
    if (ok)
      set_oil_pressure_volt(val);
  }
}

void SerialPort::openDefault() {
  for (auto info : QSerialPortInfo::availablePorts()) {
    qDebug() << info.portName() << info.description() << info.manufacturer();
    if (!info.isBusy() && (info.description().contains("Arduino") ||
                           info.manufacturer().contains("Arduino"))) {
      portInfo = info;
      break;
    }
  }

  if (portInfo.isNull()) {
    return;
  }

  arduino->setPortName(portInfo.portName());
  arduino->setBaudRate(QSerialPort::Baud115200);
  arduino->setDataBits(QSerialPort::Data8);
  arduino->setParity(QSerialPort::NoParity);
  arduino->setStopBits(QSerialPort::OneStop);
  arduino->setFlowControl(QSerialPort::NoFlowControl);

  if (arduino->open(QSerialPort::ReadWrite))
    qDebug() << "Connected to " << portInfo.manufacturer() << " on "
             << portInfo.portName();
  else
    qCritical() << "Serial Port error: " << arduino->errorString();
}

double SerialPort::get_oil_pressure_volt() const { return mOil_pressure_volt; }

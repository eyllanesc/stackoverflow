#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QLCDNumber>
#include <QLabel>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // digital clock
  QTimer *timer = new QTimer(this); // for clock
  connect(timer, &QTimer::timeout, this, &MainWindow::showTime);
  timer->start();

  // TEMP DISPLAY
  ui->lcdNumber_TMP->display("------");

  // serial port
  device = new QSerialPort(this);
  serialBuffer = "";
  line = "";

  // Identify available ports
  bool device_available = false;
  QString device_port;

  for (const QSerialPortInfo &serialPortInfo :
       QSerialPortInfo::availablePorts()) {
    if (serialPortInfo.hasProductIdentifier() &&
        serialPortInfo.hasVendorIdentifier()) {
      qDebug() << serialPortInfo.productIdentifier()
               << serialPortInfo.vendorIdentifier();
      if ((serialPortInfo.productIdentifier() == device_product_id) &&
          (serialPortInfo.vendorIdentifier() == device_vendor_id)) {
        device_available = true; // device is available on this port
        device_port = serialPortInfo.portName();
      }
    }
  }

  // Open port, if available
  if (device_available) {
    qDebug() << "Found the device port...\n";
    device->setPortName(device_port);
    device->open(QSerialPort::ReadOnly);
    device->setBaudRate(QSerialPort::Baud9600);
    device->setDataBits(QSerialPort::Data8);
    device->setFlowControl(QSerialPort::NoFlowControl);
    device->setParity(QSerialPort::NoParity);
    device->setStopBits(QSerialPort::OneStop);
    connect(device, &QIODevice::readyRead, this, &MainWindow::readSerial);
  } else {
    qDebug() << "Couldn't find the correct port for the device.\n";
  }
}

MainWindow::~MainWindow() {
  if (device->isOpen()) {
    device->close(); // close serial port if it is open
  }
  delete ui;
}

void MainWindow::readSerial() {
  serialData = device->readAll();
  serialBuffer += QString::fromStdString(serialData.toStdString());
  if (serialBuffer.indexOf("\n") >= 0) // find end line
  {
    QStringList bufferSplit = serialBuffer.split(",");
    serialBuffer.clear();
    line = bufferSplit[0];
    updateLCD(bufferSplit[0]);
  }

  // ui->lcdNumber_TMP -> display(line);
}

void MainWindow::updateLCD(QString sensor) {
  qDebug() << "What's going on?";
  qDebug() << sensor;
  ui->label_5->setText(sensor);
  ui->lcdNumber_TMP->display(sensor);
  // ui -> lcdNumber_TMP -> display(sensor);
}

void MainWindow::showTime() {
  QTime time = QTime::currentTime();                 // create time
  QString time_text = time.toString("hh : mm : ss"); // format time
  ui->DigitalClock->setText(time_text);              // make label display time
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  serial = new QSerialPort(this);

  serial->setPortName("ArduinoControl");
  serial->setBaudRate(QSerialPort::Baud19200);
  serial->setDataBits(QSerialPort::Data8);
  serial->setParity(QSerialPort::NoParity);
  serial->setStopBits(QSerialPort::OneStop);
  serial->setFlowControl(QSerialPort::NoFlowControl);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btn_fwd_clicked() { sendData(QByteArray("f")); }

void MainWindow::on_btn_bck_clicked() { sendData(QByteArray("r")); }

void MainWindow::on_btn_spd_2_clicked() { sendData(QByteArray("2")); }

void MainWindow::on_btn_spd_3_clicked() { sendData(QByteArray("3")); }

void MainWindow::on_btn_spd_4_clicked() { sendData(QByteArray("4")); }

void MainWindow::on_btn_pause_clicked() { sendData(QByteArray("R")); }

void MainWindow::on_btn_strt_clicked() { sendData(QByteArray("R")); }

void MainWindow::sendData(QByteArray ba) {
  if (serial->open(QIODevice::ReadWrite))
    if (serial->isWritable()) {
      serial->write(ba);
      serial->flush();
      serial->close();
    }
}

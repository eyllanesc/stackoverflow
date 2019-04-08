#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSerialPort;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void updateLCD(QString sensor);
private slots:
  void showTime();
  void readSerial();

private:
  Ui::MainWindow *ui;

  QSerialPort *device;
  QString serialBuffer, line;

  quint16 device_product_id = 0x0043;
  quint16 device_vendor_id = 0x2341;
  QByteArray serialData;
};

#endif // MAINWINDOW_H

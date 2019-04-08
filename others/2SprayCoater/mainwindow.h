#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_btn_fwd_clicked();
  void on_btn_bck_clicked();
  void on_btn_spd_2_clicked();
  void on_btn_spd_3_clicked();
  void on_btn_spd_4_clicked();
  void on_btn_pause_clicked();
  void on_btn_strt_clicked();

private:
  Ui::MainWindow *ui;
  QSerialPort *serial;

  void sendData(QByteArray ba);
};

#endif // MAINWINDOW_H

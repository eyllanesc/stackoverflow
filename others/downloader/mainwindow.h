#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qtdownload.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QtDownload *dl;
private slots:
  void myslot(qint64 recieved, qint64 total);
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_lineEdit_textChanged(const QString &arg1);
  void on_lineEdit_2_textChanged(const QString &arg1);
};

#endif // MAINWINDOW_H

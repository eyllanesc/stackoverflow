#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dataexchange.h"

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

  DataExchange *de;

public slots:
  void mySlot(bool value);
};

#endif // MAINWINDOW_H

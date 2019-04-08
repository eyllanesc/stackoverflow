#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "moviescreen.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  void sendRequest();
  ~MainWindow();

private slots:
  void on_pushButton_clicked();

private:
  Ui::MainWindow *ui;
  MovieScreen moviescreen;
};

#endif // MAINWINDOW_H

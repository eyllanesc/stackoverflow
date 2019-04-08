#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog.h"

#include <QMainWindow>

#include "library.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void addBook(const Book &b);
private slots:
  void on_actionAdd_triggered();

  void on_next_clicked();

  void on_previous_clicked();

private:
  Ui::MainWindow *ui;
  Dialog *d;
  int currentIndex;
  Library l;
};

#endif // MAINWINDOW_H

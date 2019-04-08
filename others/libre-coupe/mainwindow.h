#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog.h"
#include "library.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void addBook(const book &);

private slots:
  void on_next_clicked();

  void on_previous_clicked();

  void on_actionAdd_book_triggered();

private:
  Ui::MainWindow *ui;
  int currentIndex;
  library l;
};

#endif // MAINWINDOW_H

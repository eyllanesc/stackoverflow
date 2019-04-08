#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QQmlEngine;
class QQmlComponent;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  bool eventFilter(QObject *watched, QEvent *event);

private:
  void showCalendar();
  Q_SLOT void onSelectedDate();

  QObject *dialog = Q_NULLPTR;
  QQmlEngine *engine;
  QQmlComponent *component;

  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

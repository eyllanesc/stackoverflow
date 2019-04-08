#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QVideoWidget;
class QCamera;

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
  QVideoWidget *m_viewfinder;
  QCamera *m_camera;
};

#endif // MAINWINDOW_H

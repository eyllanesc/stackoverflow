#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  QPushButton *m_QPushButton_calibration;
  QCamera *m_QCamera_required_camera;
  QHBoxLayout *layout;

public slots:
  void handleButton();
};

#endif // MAINWINDOW_H

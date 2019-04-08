#ifndef CAMERAFEED_H
#define CAMERAFEED_H

#include <QMainWindow>

#include <QTimer>
#include <opencv2/opencv.hpp>
namespace Ui {
class MainWindow;
}

class CameraFeed : public QMainWindow {
  Q_OBJECT

public:
  explicit CameraFeed(QWidget *parent = 0);
  ~CameraFeed();

private slots:
  void on_start_clicked();

  void on_stop_clicked();

  void on_record_clicked();

  void on_toolButton_clicked();

private:
  Ui::MainWindow *ui;

  void initCamera();
  void initVideo();

  void processGui();

  cv::VideoWriter writer;
  cv::VideoCapture cap;
  cv::Mat frame;

  QTimer *trigger;

  bool isRecorded;
};

#endif // CAMERAFEED_H

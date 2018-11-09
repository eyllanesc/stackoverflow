#ifndef CAMERAIMAGE_H
#define CAMERAIMAGE_H

#include <QTimer>
#include <QWidget>
#include <opencv2/opencv.hpp>

class cameraimage : public QWidget
{
    Q_OBJECT
public:
    explicit cameraimage(QWidget *parent = nullptr);
private:
    QPoint mPoint;
    QTimer *timer;
    cv::VideoCapture captureVideo;

public slots:
    void startStreaming();
    void stopStreaming();

protected:
    void paintEvent(QPaintEvent *);

};

#endif // CAMERAIMAGE_H

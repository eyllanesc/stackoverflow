#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QTimer>
#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

Q_SIGNALS:
    void frameReady(cv::Mat currentFrame);
public Q_SLOTS:
    void start();
private Q_SLOTS:
    void updateFrame();
private:
    QTimer timer;
    cv::VideoCapture cap;
};

#endif // BACKEND_H

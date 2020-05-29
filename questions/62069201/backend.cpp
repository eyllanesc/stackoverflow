#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    cv::VideoCapture cap;
    connect(&timer, &QTimer::timeout, this, &Backend::updateFrame);
    timer.setInterval(30);
}

void Backend::start()
{
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
    timer.start();
}

void Backend::updateFrame()
{
    cv::Mat frame;
    cap.read(frame);
    if (!frame.empty())
        Q_EMIT frameReady(frame);
}

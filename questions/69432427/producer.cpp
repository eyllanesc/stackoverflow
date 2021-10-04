#include "producer.h"

#include <QImage>
#include <QPainter>
#include <QSize>
#include <QVideoFrame>

#include <QRandomGenerator>
#include <QDateTime>

Producer::Producer(QObject *parent):QObject(parent)
{
    m_timer.setInterval(500);
    connect(&m_timer, &QTimer::timeout, this, &Producer::handleTimeout);
}

QVideoSink *Producer::videoSink() const
{
    return m_videoSink.get();
}

void Producer::setVideoSink(QVideoSink *newVideoSink)
{
    if (m_videoSink == newVideoSink)
        return;
    m_videoSink = newVideoSink;
    emit videoSinkChanged();
}

void Producer::start()
{
    m_timer.start();
    handleTimeout();
}

void Producer::handleTimeout()
{
    if(!m_videoSink)
        return;
    QVideoFrame video_frame(QVideoFrameFormat(QSize(640, 480),QVideoFrameFormat::Format_BGRA8888));
    if(!video_frame.isValid() || !video_frame.map(QVideoFrame::WriteOnly)){
        qWarning() << "QVideoFrame is not valid or not writable";
        return;
    }
    QImage::Format image_format = QVideoFrameFormat::imageFormatFromPixelFormat(video_frame.pixelFormat());
    if(image_format == QImage::Format_Invalid){
        qWarning() << "It is not possible to obtain image format from the pixel format of the videoframe";
        return;
    }
    int plane = 0;
    QImage image(video_frame.bits(plane), video_frame.width(),video_frame.height(), image_format);
    image.fill(QColor::fromRgb(QRandomGenerator::global()->generate()));
    QPainter painter(&image);
    painter.drawText(image.rect(), Qt::AlignCenter, QDateTime::currentDateTime().toString());
    painter.end();

    video_frame.unmap();
    m_videoSink->setVideoFrame(video_frame);
}

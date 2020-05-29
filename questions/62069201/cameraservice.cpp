#include "backend.h"
#include "cameraservice.h"

#include <QAbstractVideoSurface>
#include <iostream>

CameraService::CameraService(Backend *backend, QObject *parent)
    : QObject(parent), m_backend(backend), m_isFormatSet(false)
{
    connect(m_backend.data(), &Backend::frameReady, this, &CameraService::onVideoFrameReady);
}

QAbstractVideoSurface *CameraService::videoSurface() const
{
    return m_surface;
}

void CameraService::setVideoSurface(QAbstractVideoSurface *surface){
    if (m_surface == surface)
        return;
    if(m_surface && m_surface != surface && m_surface->isActive())
        m_surface->stop();
    m_surface = surface;
    Q_EMIT surfaceChanged(m_surface);
    m_backend->start();
    if (m_surface && m_format.isValid()) {
        m_format = m_surface->nearestFormat(m_format);
        m_surface->start(m_format);
    }
}

void CameraService::setFormat(
        int width,
        int height,
        QVideoFrame::PixelFormat frameFormat
        ){
    QSize size(width, height);
    QVideoSurfaceFormat format(size, frameFormat);
    m_format = format;
    if (m_surface) {
        if (m_surface->isActive())
            m_surface->stop();
        m_format = m_surface->nearestFormat(m_format);
        m_surface->start(m_format);
    }
}

void CameraService::onVideoFrameReady(cv::Mat currentFrame){
    if (!m_surface || currentFrame.empty())
        return;
    cv::Mat continuousFrame;
    if (!currentFrame.isContinuous())
        continuousFrame = currentFrame.clone();
    else
        continuousFrame = currentFrame;
    if (!m_isFormatSet) {
        setFormat(continuousFrame.cols,
                  continuousFrame.rows,
                  QVideoFrame::Format_RGB32);
        m_isFormatSet = true;
    }
    m_image = QImage(continuousFrame.data,
                     continuousFrame.cols,
                     continuousFrame.rows,
                     continuousFrame.step,
                     QImage::Format_RGB888);
    m_image = m_image.rgbSwapped();
    m_image.convertTo(QVideoFrame::imageFormatFromPixelFormat(QVideoFrame::Format_RGB32));
    m_surface->present(QVideoFrame(m_image));
}

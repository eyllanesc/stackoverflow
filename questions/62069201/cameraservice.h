#ifndef CAMERASERVICE_H
#define CAMERASERVICE_H

#include "backend.h"

#include <QObject>
#include <QPointer>
#include <QVideoFrame>
#include <QVideoSurfaceFormat>
#include <opencv2/core/mat.hpp>

class QAbstractVideoSurface;

class CameraService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface* videoSurface READ videoSurface WRITE setVideoSurface NOTIFY surfaceChanged)
public:
    explicit CameraService(Backend *backend, QObject *parent = nullptr);
    QAbstractVideoSurface* videoSurface() const;

public Q_SLOTS:
    void setVideoSurface(QAbstractVideoSurface* surface);
Q_SIGNALS:
    void surfaceChanged(QAbstractVideoSurface* surface);
private Q_SLOTS:
    void onVideoFrameReady(cv::Mat currentFrame);
private:
    void setFormat(int width, int height, QVideoFrame::PixelFormat frameFormat);

    QPointer<QAbstractVideoSurface> m_surface;
    QScopedPointer<Backend> m_backend;
    QVideoSurfaceFormat m_format;
    bool m_isFormatSet;
    QImage m_image;
};

#endif // CAMERASERVICE_H

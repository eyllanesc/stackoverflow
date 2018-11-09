#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QPainter>
#include <QTime>

class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider():QQuickImageProvider(QQuickImageProvider::Image){
        qsrand(QTime::currentTime().msec());
    }
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize){
        int width = 100;
        int height = 50;
        if (size)
            *size = QSize(width, height);
        QImage img(requestedSize.width() > 0 ? requestedSize.width() : width,
               requestedSize.height() > 0 ? requestedSize.height() : height, QImage::Format_RGB32);
        img.fill(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
        QPainter painter(&img);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.drawText(QRectF(QPointF(0, 0), img.size()),  Qt::AlignCenter,
                         QTime::currentTime().toString("hh:mm:ss.z")+" "+id);
        painter.end();
        return img;
    }
};

#endif // IMAGEPROVIDER_H


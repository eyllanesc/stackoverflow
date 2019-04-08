#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>

class ImageProvider : public QQuickImageProvider {
public:
  ImageProvider();
  QImage requestImage(const QString &id, QSize *size,
                      const QSize &requestedSize) override;
};

#endif // IMAGEPROVIDER_H

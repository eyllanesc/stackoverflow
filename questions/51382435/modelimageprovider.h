#ifndef MODELIMAGEPROVIDER_H
#define MODELIMAGEPROVIDER_H

#include "item.h"

#include <QAbstractListModel>
#include <QQuickImageProvider>
#include <QUuid>

class ModelImageProvider : public QQuickImageProvider {
public:
  explicit ModelImageProvider(QAbstractItemModel *model)
      : QQuickImageProvider(QQuickImageProvider::Image) {
    mModel = model;
  }
  QImage requestImage(const QString &id, QSize *size,
                      const QSize &requestedSize) {
    int width = 100;
    int height = 50;
    Q_UNUSED(requestedSize)
    if (size)
      *size = QSize(width, height);
    QUuid uuid(QByteArray::fromPercentEncoding(id.toLatin1()));
    QModelIndexList indexes =
        mModel->match(mModel->index(0, 0), Qt::UserRole + 1,
                      QVariant::fromValue(uuid), 1, Qt::MatchRecursive);
    if (indexes.size() > 0) {
      Item *it = qvariant_cast<Item *>(indexes[0].data(Qt::UserRole));
      if (it)
        return it->photo();
    }
    return QImage();
  }

private:
  QAbstractItemModel *mModel;
};

#endif // MODELIMAGEPROVIDER_H

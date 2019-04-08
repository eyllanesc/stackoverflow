#ifndef ITEM_H
#define ITEM_H

#include <QImage>
#include <QObject>
#include <QUuid>

class Item : public QObject {
  Q_OBJECT
  Q_PROPERTY(QImage photo READ photo WRITE setPhoto NOTIFY photoChanged)
  Q_PROPERTY(QUuid uuid READ uuid NOTIFY uuidChanged)
public:
  explicit Item(QObject *parent = nullptr) : QObject(parent) {}

  QImage photo() const { return mPhoto; }
  void setPhoto(const QImage &photo) {
    mPhoto = photo;
    emit photoChanged();
    mUuid = QUuid::createUuid();
    emit uuidChanged();
  }
  QUuid uuid() const { return mUuid; }
signals:
  void photoChanged();
  void uuidChanged();

private:
  QImage mPhoto;
  QUuid mUuid;
};

#endif // ITEM_H

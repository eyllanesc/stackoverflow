#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include "item.h"

#include <QAbstractListModel>

class ItemModel : public QAbstractListModel {
  Q_OBJECT
public:
  using QAbstractListModel::QAbstractListModel;
  ~ItemModel() {
    qDeleteAll(mItems);
    mItems.clear();
  }
  int rowCount(const QModelIndex &parent = QModelIndex()) const override {
    if (parent.isValid())
      return 0;
    return mItems.size();
  }

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override {
    if (!index.isValid())
      return QVariant();
    Item *item = mItems[index.row()];
    if (role == Qt::UserRole) {
      return QVariant::fromValue(item);
    } else if (role == Qt::UserRole + 1) {
      return QVariant::fromValue(item->uuid());
    }
    return QVariant();
  }

  void appendItem(Item *sample) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    mItems << sample;
    endInsertRows();
  }

  QHash<int, QByteArray> roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole] = "item";
    roles[Qt::UserRole + 1] = "uuid";
    return roles;
  }

private:
  QList<Item *> mItems;
};

#endif // ITEMMODEL_H

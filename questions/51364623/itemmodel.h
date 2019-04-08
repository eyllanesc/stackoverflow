#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H

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
    if (role == Qt::UserRole) {
      Item *item = mItems[index.row()];
      return QVariant::fromValue(item);
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
    roles[Qt::UserRole] = "sample";
    return roles;
  }

private:
  QList<Item *> mItems;
};

#endif // SAMPLEMODEL_H

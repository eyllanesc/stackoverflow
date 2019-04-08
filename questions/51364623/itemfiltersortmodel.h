#ifndef FILTERPROXYMODEL_H
#define FILTERPROXYMODEL_H

#include "item.h"

#include <QDebug>
#include <QSortFilterProxyModel>

class ItemFilterProxyModel : public QSortFilterProxyModel {
  Q_OBJECT
  Q_PROPERTY(Item *currentItem READ currentItem WRITE setCurrentItem NOTIFY
                 currentItemChanged)
public:
  using QSortFilterProxyModel::QSortFilterProxyModel;
  Item *currentItem() const { return mCurrentItem; }
  void setCurrentItem(Item *currentItem) {
    qDebug() << currentItem->getVar();
    if (mCurrentItem == currentItem)
      return;
    mCurrentItem = currentItem;
    emit currentItemChanged();
  }
  bool filterAcceptsRow(int source_row,
                        const QModelIndex &source_parent) const {
    return true;
  }
signals:
  void currentItemChanged();

private:
  Item *mCurrentItem;
};

#endif // FILTERPROXYMODEL_H

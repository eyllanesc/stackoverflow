#ifndef ITEMFILTERPROXYMODEL_H
#define ITEMFILTERPROXYMODEL_H

#include "item.h"
#include <QSortFilterProxyModel>

class ItemFilterProxyModel : public QSortFilterProxyModel {
  Q_OBJECT
public:
  using QSortFilterProxyModel::QSortFilterProxyModel;
  bool filterAcceptsRow(int source_row,
                        const QModelIndex &source_parent) const {
    Q_UNUSED(source_parent)
    return source_row % 2 == 0;
  }
};

#endif // ITEMFILTERPROXYMODEL_H

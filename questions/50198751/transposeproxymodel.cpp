#include "transposeproxymodel.h"

QModelIndex
TransposeProxyModel::mapToSource(const QModelIndex &proxyIndex) const {
  if (sourceModel()) {
    return sourceModel()->index(proxyIndex.column(), proxyIndex.row());
  } else {
    return QModelIndex();
  }
}

QModelIndex
TransposeProxyModel::mapFromSource(const QModelIndex &sourceIndex) const {
  return index(sourceIndex.column(), sourceIndex.row());
}

QModelIndex TransposeProxyModel::index(int row, int column,
                                       const QModelIndex &) const {
  return createIndex(row, column, (void *)0);
}

QModelIndex TransposeProxyModel::parent(const QModelIndex &) const {
  return QModelIndex();
}

int TransposeProxyModel::rowCount(const QModelIndex &) const {
  return sourceModel() ? sourceModel()->columnCount() : 0;
}

int TransposeProxyModel::columnCount(const QModelIndex &) const {
  return sourceModel() ? sourceModel()->rowCount() : 0;
}

QVariant TransposeProxyModel::headerData(int section,
                                         Qt::Orientation orientation,
                                         int role) const {
  if (!sourceModel()) {
    return QVariant();
  }
  Qt::Orientation new_orientation =
      orientation == Qt::Horizontal ? Qt::Vertical : Qt::Horizontal;
  return sourceModel()->headerData(section, new_orientation, role);
}

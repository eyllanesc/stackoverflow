#include "appendproxymodel.h"

QVariant AppendProxyModel::data(const QModelIndex &index, int role) const {
  if (index.row() >= 0 && index.row() < mDefaults.size() &&
      role == Qt::DisplayRole) {
    return mDefaults[index.row()];
  }
  if (index.row() >= mDefaults.size() && index.row() < rowCount()) {
    return QIdentityProxyModel::data(
        QIdentityProxyModel::index(index.row() - mDefaults.size(),
                                   index.column()),
        role);
  }
  return QIdentityProxyModel::data(index, role);
}

int AppendProxyModel::rowCount(const QModelIndex &parent) const {
  return mDefaults.size() + QIdentityProxyModel::rowCount(parent);
}

QModelIndex AppendProxyModel::index(int row, int column,
                                    const QModelIndex &parent) const {
  if (row < rowCount() - mDefaults.size())
    QIdentityProxyModel::index(row, column, parent);
  return createIndex(row, column);
}

QStringList AppendProxyModel::defaults() const { return mDefaults; }

void AppendProxyModel::setDefaults(const QStringList &defaults) {
  mDefaults = defaults;
  emit dataChanged(index(0, 0, QModelIndex()),
                   index(rowCount(), columnCount(), QModelIndex()));
}

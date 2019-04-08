#include "datasourcemodel.h"

DataSourceModel::DataSourceModel(QObject *parent) : QAbstractListModel(parent) {
  for (int i = 0; i < 10; i++) {
    Data _d{QString::number(i), i};
    d.append(_d);
  }
}

QVariantMap DataSourceModel::get(int row) const {
  QHash<int, QByteArray> names = roleNames();
  QHashIterator<int, QByteArray> i(names);
  QVariantMap res;
  QModelIndex idx = index(row, 0);
  while (i.hasNext()) {
    i.next();
    if (i.key() != AllRole) {
      QVariant data = idx.data(i.key());
      res[i.value()] = data;
    }
  }
  return res;
}

int DataSourceModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;
  return d.length();
}

QVariant DataSourceModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();
  const Data &_d = d.at(index.row());
  if (role == NameRole)
    return _d.name;
  else if (role == ValueRole)
    return _d.value;
  else if (role == AllRole) {
    return get(index.row());
  }
  return QVariant();
}

bool DataSourceModel::setData(const QModelIndex &index, const QVariant &value,
                              int role) {
  Data &_d = d[index.row()];
  if (data(index, role) != value) {
    if (role == NameRole)
      _d.name = value.toString();
    else if (role == ValueRole)
      _d.value = value.toInt();
    emit dataChanged(index, index, QVector<int>() << role << AllRole);
    return true;
  }
  return false;
}

Qt::ItemFlags DataSourceModel::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return Qt::NoItemFlags;
  return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> DataSourceModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[NameRole] = "name";
  roles[ValueRole] = "value";
  roles[AllRole] = "all";
  return roles;
}

#include "userlistmodel.h"

#include <QDebug>

UserListModel::UserListModel(QObject *parent) : QAbstractListModel(parent) {}

int UserListModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;
  return users.size();
}

QVariant UserListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();
  if (role != Qt::DisplayRole)
    return QVariant();
  if (index.row() >= users.size())
    return QVariant();
  return QVariant::fromValue<UserInfo>(users.at(index.row()));
}

bool UserListModel::setData(const QModelIndex &index, const QVariant &value,
                            int role) {
  qDebug() << index.isValid();
  qDebug() << (role == Qt::EditRole);
  qDebug() << value.canConvert<UserInfo>();
  if (index.isValid() && role == Qt::EditRole && value.canConvert<UserInfo>()) {

    users.replace(index.row(), value.value<UserInfo>());
    emit dataChanged(index, index);
    return true;
  }
  return false;
}

QVariant UserListModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const {

  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal)
    return QString("Column %1").arg(section);
  else
    return QString("Row %1").arg(section);
}

bool UserListModel::insertRows(int position, int rows,
                               const QModelIndex &parent) {
  Q_UNUSED(parent)
  beginInsertRows(QModelIndex(), position, position + rows - 1);
  for (int row = 0; row < rows; ++row) {
    users.insert(position, UserInfo());
  }
  endInsertRows();
  return true;
}

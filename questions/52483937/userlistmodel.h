#ifndef USERLISTMODEL_H
#define USERLISTMODEL_H

#include "userinfo.h"

#include <QAbstractListModel>

class UserListModel : public QAbstractListModel {
public:
  UserListModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;

  bool setData(const QModelIndex &index, const QVariant &value, int role);
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;

  bool insertRows(int position, int row,
                  const QModelIndex &parent = QModelIndex());

private:
  QList<UserInfo> users;
};
#endif // USERLISTMODEL_H

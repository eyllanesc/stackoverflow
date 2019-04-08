#include "mymodel.h"
#include "data.h"
#include <iostream>

MyModel::MyModel(QObject *parent)
    : QAbstractListModel(parent), mDatas(nullptr) {
  std::cout << "inside Model constructed" << std::endl;
}

int MyModel::rowCount(const QModelIndex &parent) const {
  // For list models only the root node (an invalid parent) should return the
  // list's size. For all other (valid) parents, rowCount() should return 0 so
  // that it does not become a tree model.
  if (parent.isValid())
    return 0;

  // FIXME: Implement me!

  return mDatas->items().size();
}

QVariant MyModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();
  const unit item = mDatas->items().at(index.row());

  // FIXME: Implement me!
  switch (role) {
  case NameRole:
    return QVariant(QStringLiteral("!11"));
  case LevelRole:
    return QVariant(QStringLiteral("!21"));
  case ParentRole:
    return QVariant(item.parent);
  case SublevelRole:
    return item.subNodes;
  }
  return QVariant();
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value,
                      int role) {
  if (!mDatas)
    return false;

  unit item = mDatas->items().at(index.row());
  switch (role) {
  case NameRole:
    item.name = value.toString();
    break;
  case LevelRole:
    item.level = value.toString();
    break;
  case ParentRole:
    item.parent = value.toString();
    break;
  case SublevelRole:
    item.subNodes.append(value);
    break;
  }
  if (mDatas->setItemAt(index.row(), item)) {
    // FIXME: Implement me!
    emit dataChanged(index, index, QVector<int>{role});
    return true;
  }
  return false;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return Qt::NoItemFlags;

  return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> MyModel::roleNames() const {
  QHash<int, QByteArray> names;
  names[NameRole] = "name";
  names[LevelRole] = "level";
  names[ParentRole] = "parent";
  names[SublevelRole] = "subNode";
  return names;
}

Data *MyModel::datas() const { return mDatas; }

void MyModel::setDatas(Data *data) {
  beginResetModel();
  if (mDatas)
    mDatas->disconnect(this);

  delete mDatas;
  mDatas = data;

  if (mDatas) {
    connect(mDatas, &Data::preItemAppended, this, [=]() {
      const int index = mDatas->items().size();
      beginInsertRows(QModelIndex(), index, index);
    });
    connect(mDatas, &Data::postItemAppended, this, &MyModel::endInsertRows);

    connect(mDatas, &Data::preItemRemoved, this,
            [=](int index) { beginRemoveRows(QModelIndex(), index, index); });

    connect(mDatas, &Data::postItemRemoved, this, &MyModel::endRemoveRows);
  }

  endResetModel();
}

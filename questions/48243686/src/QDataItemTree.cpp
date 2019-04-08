#include "QDataItemTree.h"
#include <QStringList>

QDataItemTree::QDataItemTree(const QString &data, QObject *parent)
    : QAbstractItemModel(parent) {
  QList<QVariant> rootData;
  rootData << data;
  rootItem = new QDataItem(rootData);
}

QDataItemTree::~QDataItemTree() { delete rootItem; }

QVariant QDataItemTree::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (role != Qt::DisplayRole)
    return QVariant();

  QDataItem *item = static_cast<QDataItem *>(index.internalPointer());
  return item->data(index.column());
}

Qt::ItemFlags QDataItemTree::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return 0;

  return QAbstractItemModel::flags(index);
}

QVariant QDataItemTree::headerData(int section, Qt::Orientation orientation,
                                   int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return rootItem->data(section);
  return QVariant();
}

QModelIndex QDataItemTree::index(int row, int column,
                                 const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  QDataItem *parentItem;

  if (!parent.isValid())
    parentItem = rootItem;
  else
    parentItem = static_cast<QDataItem *>(parent.internalPointer());

  QDataItem *childItem = parentItem->child(row);
  if (childItem)
    return createIndex(row, column, childItem);
  else
    return QModelIndex();
}

QModelIndex QDataItemTree::parent(const QModelIndex &index) const {
  if (!index.isValid())
    return QModelIndex();

  QDataItem *childItem = static_cast<QDataItem *>(index.internalPointer());
  QDataItem *parentItem = childItem->parentItem();

  if (parentItem == rootItem)
    return QModelIndex();

  return createIndex(parentItem->row(), 0, parentItem);
}

int QDataItemTree::rowCount(const QModelIndex &parent) const {
  QDataItem *parentItem;
  if (parent.column() > 0)
    return 0;

  if (!parent.isValid())
    parentItem = rootItem;
  else
    parentItem = static_cast<QDataItem *>(parent.internalPointer());

  return parentItem->childCount();
}

int QDataItemTree::columnCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return static_cast<QDataItem *>(parent.internalPointer())->columnCount();
  else
    return rootItem->columnCount();
}

QDataItem *QDataItemTree::addBatch(int number) {
  QString name = "Batch_" + QString::number(number);
  QList<QVariant> d;
  d << name;
  QDataItem *batch = new QDataItem(d, rootItem);
  beginInsertRows(indexFromItem(rootItem), rootItem->childCount(),
                  rootItem->childCount());
  rootItem->appendChild(batch);
  endInsertRows();
  return batch;
}

QDataItem *QDataItemTree::addBatchElement(int number, QDataItem *parent) {
  QString name = "Element_" + QString::number(number);
  QList<QVariant> d;
  d << name;
  QDataItem *element = new QDataItem(d, parent);
  beginInsertRows(indexFromItem(parent), parent->childCount(),
                  parent->childCount());
  parent->appendChild(element);
  endInsertRows();
  return element;
}

QDataItem *QDataItemTree::addBatchElementChild(int number, QDataItem *parent) {
  QString name = "Child_" + QString::number(number);
  QList<QVariant> d;
  d << name;
  QDataItem *element_child = new QDataItem(d, parent);
  beginInsertRows(indexFromItem(parent), parent->childCount(),
                  parent->childCount());
  parent->appendChild(element_child);
  endInsertRows();
  return element_child;
}

QModelIndex QDataItemTree::indexFromItem(QDataItem *item) {
  if (item == rootItem || item == NULL)
    return QModelIndex();
  QDataItem *parent = item->parentItem();

  QList<QDataItem *> parents;

  while (parent && parent != rootItem) {
    parents << parent;
    parent = parent->parentItem();
  }
  QModelIndex ix;
  parent = rootItem;
  /*for(auto ch: parents){
      ix = index(ch->row(), 0, ix);
  }*/

  for (int i = 0; i < parents.count(); i++) {
    ix = index(parents[i]->row(), 0, ix);
  }
  ix = index(ix.row(), 0, ix);
  return ix;
}

#ifndef QDataItemTREE_H
#define QDataItemTREE_H

#include <QAbstractItemModel>

#include "QDataItem.h"

class QDataItemTree : public QAbstractItemModel {
  Q_OBJECT
public:
  explicit QDataItemTree(const QString &data, QObject *parent = 0);
  ~QDataItemTree();

  QVariant data(const QModelIndex &index, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QDataItem *addBatch(int number);
  QDataItem *addBatchElement(int number, QDataItem *parent);
  QDataItem *addBatchElementChild(int number, QDataItem *parent);

  QModelIndex indexFromItem(QDataItem *item);

private:
  QDataItem *rootItem;
};

#endif // QDataItemTREE_H

#include "sqlrelationaltablemodel.h"

#include <QBrush>

SqlRelationalTableModel::SqlRelationalTableModel(QObject *parent,
                                                 QSqlDatabase db)
    : QSqlRelationalTableModel(parent, db) {}

QVariant SqlRelationalTableModel::data(const QModelIndex &item,
                                       int role) const {
  if (role == Qt::BackgroundRole)
    if (QSqlRelationalTableModel::data(index(item.row(), 2), Qt::DisplayRole)
            .toString()
            .trimmed() == "Lima")
      return QVariant(QBrush(Qt::red));
  return QSqlRelationalTableModel::data(item, role);
}

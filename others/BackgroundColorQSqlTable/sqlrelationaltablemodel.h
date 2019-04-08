#ifndef SQLRELATIONALTABLEMODEL_H
#define SQLRELATIONALTABLEMODEL_H

#include <QSqlRelationalTableModel>

class SqlRelationalTableModel : public QSqlRelationalTableModel {
  Q_OBJECT
public:
  SqlRelationalTableModel(QObject *parent = 0,
                          QSqlDatabase db = QSqlDatabase());

  QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;
};

#endif // SQLRELATIONALTABLEMODEL_H

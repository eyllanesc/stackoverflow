#ifndef DATASOURCEMODEL_H
#define DATASOURCEMODEL_H

#include "datasourceobject.h"
#include <QAbstractListModel>

class DataSourceModel : public QAbstractListModel {
  Q_OBJECT

public:
  enum datasourceRoles {
    idRole = Qt::UserRole + 1000,
    nameRole,
    displaynameRole,
    valueRole,
    allRole
  };

  explicit DataSourceModel(QObject *parent = nullptr);
  void addDataSourceObject(const DataSourceObject &dataSourceObject);
  Q_INVOKABLE QVariantMap get(int row) const;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QHash<int, QByteArray> roleNames() const override;

private:
  QList<DataSourceObject> m_DataSourceObjects;
};

#endif // DATASOURCEMODEL_H

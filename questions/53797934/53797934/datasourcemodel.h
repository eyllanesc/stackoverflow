#ifndef DATASOURCEMODEL_H
#define DATASOURCEMODEL_H

#include <QAbstractListModel>

struct Data {
  QString name;
  int value;
};

class DataSourceModel : public QAbstractListModel {
  Q_OBJECT
public:
  enum DataRoles { NameRole = Qt::UserRole + 1000, ValueRole, AllRole };
  explicit DataSourceModel(QObject *parent = nullptr);
  QVariantMap get(int row) const;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;
  QHash<int, QByteArray> roleNames() const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
  QList<Data> d;
};

#endif // DATASOURCEMODEL_H

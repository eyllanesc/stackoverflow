#ifndef ASSETLISTMODEL_H
#define ASSETLISTMODEL_H

#include "assetitem.h"
class NodeModel;
class QQmlContext;
#include <QAbstractListModel>

struct Data {
  QGeoCoordinate coord;
  int angle;
};
Q_DECLARE_METATYPE(Data)

class AssetListModel : public QAbstractListModel {
  Q_OBJECT

public:
  explicit AssetListModel(QObject *parent = nullptr);
  enum AirportsRoles {
    NameRole = Qt::UserRole + 1,
    AssetRole,
    HistoryRole,
    AngleRole,
    ColorRole
  };

  void register_objects(const QString &assetName, const QString &nodeName,
                        QQmlContext *context);

  Q_INVOKABLE bool addAsset(QGeoCoordinate coord, int angle,
                            const QString &name);
  Q_INVOKABLE bool createAsset(QGeoCoordinate coord, const QColor &color,
                               const QString &name);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role) override;

private:
  QList<AssetItem> mAssets;
  NodeModel *model;
};

#endif // ASSETLISTMODEL_H

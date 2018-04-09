#ifndef ASSETLISTMODEL_H
#define ASSETLISTMODEL_H

#include "assetitem.h"

#include <QAbstractListModel>

class AssetListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    using QAbstractListModel::QAbstractListModel;

    enum AirportsRoles{
        NameRole = Qt::UserRole + 1,
        AssetRole,
        HistoryRole,
        ColorRole
    };

    Q_INVOKABLE bool addAsset(QGeoCoordinate coord, const QString & name);
    bool createAsset(QGeoCoordinate coord, const QString & name);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
private:
    QList<AssetItem> mAssets;
};

#endif // ASSETLISTMODEL_H

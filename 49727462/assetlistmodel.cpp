#include "assetlistmodel.h"

bool AssetListModel::addAsset(QGeoCoordinate coord, const QString &name)
{
    auto it = std::find_if(mAssets.begin(), mAssets.end(), [&](AssetItem const& obj){
            return obj.name() == name;
} );
    if(it != mAssets.end()){
        //append
        int row = it - mAssets.begin();
        QModelIndex ix = index(row);
        return  setData(ix, QVariant::fromValue(coord), AssetRole);
    }
    else{
        //create
        return createAsset(coord, name);
    }
}

bool AssetListModel::createAsset(QGeoCoordinate coord, const QString &name)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    AssetItem it;
    it.setName(name);
    it.setAsset(coord);
    it.setColor(QColor(qrand()%255, qrand()%255, qrand()%255));
    mAssets<< it;
    endInsertRows();
    return true;
}


int AssetListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mAssets.count();
}

QVariant AssetListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(index.row() >= 0 && index.row()<rowCount()){
        const AssetItem &it = mAssets[index.row()];
        if(role==NameRole)
            return it.name();
        else if (role == AssetRole)
            return  QVariant::fromValue(it.asset());
        else if(role == HistoryRole){
            QVariantList history_list;
            QList<QGeoCoordinate> coords = it.getHistory();
            for(const QGeoCoordinate & coord: coords){
                history_list<<QVariant::fromValue(coord);
            }
            return history_list;
        }
        else if(role == ColorRole){
            return it.getColor();
        }
    }
    return QVariant();
}


QHash<int, QByteArray> AssetListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AssetRole]= "asset";
    roles[HistoryRole] = "history";
    roles[ColorRole] = "color";
    return roles;
}

bool AssetListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if(index.row() >= 0 && index.row()<rowCount()){
        if (role == AssetRole) {
            QGeoCoordinate new_asset(value.value<QGeoCoordinate>());
            mAssets[index.row()].setAsset(new_asset);
            emit dataChanged(index, index, QVector<int>{AssetRole});
            return true;
        }
    }
    return false;
}

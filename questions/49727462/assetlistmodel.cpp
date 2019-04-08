#include "assetlistmodel.h"
#include "nodemodel.h"

#include <QQmlContext>

AssetListModel::AssetListModel(QObject *parent) : QAbstractListModel(parent) {
  model = new NodeModel{this};
}

void AssetListModel::register_objects(const QString &assetName,
                                      const QString &nodeName,
                                      QQmlContext *context) {
  context->setContextProperty(assetName, this);
  context->setContextProperty(nodeName, model);
}

bool AssetListModel::addAsset(QGeoCoordinate coord, int angle,
                              const QString &name) {
  auto it =
      std::find_if(mAssets.begin(), mAssets.end(),
                   [&](AssetItem const &obj) { return obj.name() == name; });
  if (it != mAssets.end()) {
    // append
    int row = it - mAssets.begin();
    QModelIndex ix = index(row);
    QGeoCoordinate c = ix.data(AssetRole).value<QGeoCoordinate>();
    int a = ix.data(AngleRole).toInt();
    Data data{coord, angle};
    bool result = setData(ix, QVariant::fromValue(data), AssetRole);
    if (result)
      model->appendNode(c, a);
    return result;
  }
  return false;
}

bool AssetListModel::createAsset(QGeoCoordinate coord, const QColor &color,
                                 const QString &name) {
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  AssetItem it;
  it.setName(name);
  it.setAsset(coord);
  it.setColor(color);
  mAssets << it;
  endInsertRows();
  return true;
}

int AssetListModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return mAssets.count();
}

QVariant AssetListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();
  if (index.row() >= 0 && index.row() < rowCount()) {
    const AssetItem &it = mAssets[index.row()];
    if (role == NameRole)
      return it.name();
    else if (role == AssetRole)
      return QVariant::fromValue(it.asset());
    else if (role == HistoryRole) {
      QVariantList history_list;
      QList<QGeoCoordinate> coords = it.getHistory();
      for (const QGeoCoordinate &coord : coords) {
        history_list << QVariant::fromValue(coord);
      }
      history_list << QVariant::fromValue(it.asset());
      return history_list;
    } else if (role == ColorRole) {
      return it.getColor();
    } else if (role == AngleRole) {
      return it.getAngle();
    }
  }
  return QVariant();
}

QHash<int, QByteArray> AssetListModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[NameRole] = "nameData";
  roles[AssetRole] = "assetData";
  roles[HistoryRole] = "historyData";
  roles[AngleRole] = "angleData";
  roles[ColorRole] = "colorData";
  return roles;
}

bool AssetListModel::setData(const QModelIndex &index, const QVariant &value,
                             int role) {
  if (!index.isValid())
    return false;
  if (index.row() >= 0 && index.row() < rowCount()) {
    if (role == AssetRole) {
      const Data &data = value.value<Data>();
      QGeoCoordinate new_asset(data.coord);
      mAssets[index.row()].setAsset(new_asset);
      mAssets[index.row()].setAngle(data.angle);
      emit dataChanged(index, index, QVector<int>{AssetRole});
      return true;
    }
  }
  return false;
}

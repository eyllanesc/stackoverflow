#include "locationmodel.h"

LocationModel::LocationModel(QObject *parent) : QAbstractListModel(parent) {}

int LocationModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return m_locations.count();
}

QVariant LocationModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || (index.row() < 0 && index.row() >= rowCount()))
    return QVariant();
  Location *location = m_locations[index.row()];
  if (role == LatitudeRole) {
    return location->latitude();
  } else if (role == LongitudeRole) {
    return location->longitude();
  } else if (role == PositionRole) {
    return QVariant::fromValue(location->coordinate());
  }
  return QVariant();
}

QHash<int, QByteArray> LocationModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[LatitudeRole] = "latitude";
  roles[LongitudeRole] = "longitude";
  roles[PositionRole] = "position";
  return roles;
}

QQmlListProperty<Location> LocationModel::locations() {
  return QQmlListProperty<Location>(
      this, this, &LocationModel::appendLocation, &LocationModel::locationCount,
      &LocationModel::location, &LocationModel::clearLocations);
}

void LocationModel::appendLocation(double latitude, double longitude) {
  Location *loc = new Location;
  loc->setLatitude(latitude);
  loc->setLongitude(longitude);
  appendLocation(loc);
}
void LocationModel::appendLocation(const QGeoCoordinate &coordinate) {
  Location *loc = new Location;
  loc->setCoordinate(coordinate);
  appendLocation(loc);
}

void LocationModel::appendLocation(Location *location) {
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_locations.append(location);
  endInsertRows();
}

Location *LocationModel::location(int ix) const { return m_locations.at(ix); }

void LocationModel::clearLocations() {
  beginResetModel();
  m_locations.clear();
  endResetModel();
}

void LocationModel::appendLocation(QQmlListProperty<Location> *list,
                                   Location *p) {
  reinterpret_cast<LocationModel *>(list->data)->appendLocation(p);
}

int LocationModel::locationCount(QQmlListProperty<Location> *list) {
  return reinterpret_cast<LocationModel *>(list->data)->rowCount();
}

Location *LocationModel::location(QQmlListProperty<Location> *list, int i) {
  return reinterpret_cast<LocationModel *>(list->data)->location(i);
}

void LocationModel::clearLocations(QQmlListProperty<Location> *list) {
  reinterpret_cast<LocationModel *>(list->data)->clearLocations();
}

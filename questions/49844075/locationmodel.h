#ifndef LOCATIONMODEL_H
#define LOCATIONMODEL_H

#include "location.h"

#include <QAbstractListModel>
#include <QQmlListProperty>

class LocationModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<Location> locations READ locations)
public:
  explicit LocationModel(QObject *parent = nullptr);
  enum LocationRoles {
    LatitudeRole = Qt::UserRole + 1,
    LongitudeRole,
    PositionRole
  };

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  QQmlListProperty<Location> locations();

  Q_INVOKABLE void appendLocation(double latitude, double longitude);
  Q_INVOKABLE void appendLocation(const QGeoCoordinate &coordinate);
  void appendLocation(Location *location);
  Location *location(int ix) const;
  void clearLocations();

private:
  static void appendLocation(QQmlListProperty<Location> *, Location *);
  static int locationCount(QQmlListProperty<Location> *);
  static Location *location(QQmlListProperty<Location> *, int);
  static void clearLocations(QQmlListProperty<Location> *);

  QVector<Location *> m_locations;
};

#endif // LOCATIONMODEL_H

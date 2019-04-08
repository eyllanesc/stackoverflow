#ifndef LOCATION_H
#define LOCATION_H

#include <QGeoCoordinate>
#include <QObject>

class Location : public QObject {
  Q_OBJECT
  Q_PROPERTY(double longitude READ longitude WRITE setLongitude NOTIFY
                 longitudeChanged)
  Q_PROPERTY(
      double latitude READ latitude WRITE setLatitude NOTIFY latitudeChanged)
  Q_PROPERTY(QGeoCoordinate coordinate READ coordinate WRITE setCoordinate
                 NOTIFY coordinateChanged)
public:
  Location(QObject *parent = 0) : QObject(parent), m_coordinate{0, 0} {}

  Q_SIGNAL void longitudeChanged();
  Q_SIGNAL void latitudeChanged();
  Q_SIGNAL void coordinateChanged();

  double longitude() const { return m_coordinate.longitude(); }
  void setLongitude(double longitude) {
    if (m_coordinate.longitude() == longitude)
      return;
    m_coordinate.setLongitude(longitude);
    Q_EMIT longitudeChanged();
  }

  double latitude() const { return m_coordinate.latitude(); }
  void setLatitude(double latitude) {
    if (m_coordinate.latitude() == latitude)
      return;
    m_coordinate.setLatitude(latitude);
    Q_EMIT latitudeChanged();
  }

  QGeoCoordinate coordinate() const { return m_coordinate; }
  void setCoordinate(const QGeoCoordinate &coordinate) {
    if (coordinate == m_coordinate)
      return;
    m_coordinate = coordinate;
    Q_EMIT coordinateChanged();
  }

private:
  QGeoCoordinate m_coordinate;
};

#endif // LOCATION_H

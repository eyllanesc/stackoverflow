#ifndef AIRPORT_H
#define AIRPORT_H

#include <QGeoCoordinate>
#include <QString>

class Runway {
public:
  Runway(QString name, int qfu, double latitude, double longitude,
         double elevation)
      : m_name(name), m_qfu(qfu) {
    m_position.setLatitude(latitude);
    m_position.setLongitude(longitude);
    m_position.setAltitude(elevation);
  }

  QString nameRunway() const { return m_name; }

  int runwayQfu() const { return m_qfu; }
  QGeoCoordinate rwPosition() const { return m_position; }

private:
  QGeoCoordinate m_position;
  QString m_name;
  int m_qfu;
};

class Airport {
public:
  Airport(QString code, QString name, double latitude, double longitude,
          double elevation)
      : m_code(code), m_name(name) {

    m_position.setLatitude(latitude);
    m_position.setLongitude(longitude);
    m_position.setAltitude(elevation);
  }

  QGeoCoordinate apPosition() const { return m_position; }
  QString oaciCode() const { return m_code; }
  QString airportName() const { return m_name; }

  void addRunway(const Runway &runway) { m_runwayList << runway; }
  const QList<Runway> &listRunways() const { return m_runwayList; }

private:
  QGeoCoordinate m_position;
  QString m_code;
  QString m_name;
  QList<Runway> m_runwayList;
};

#endif // AIRPORT_H

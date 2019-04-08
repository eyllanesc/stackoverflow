#ifndef FLIGHTROUTE_H
#define FLIGHTROUTE_H

#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
struct FPlanWPT {
  QString name;
  double longitude;
  double latitude;
  double bearing;
  QJsonObject toObject() const {
    QJsonObject obj;
    obj["name"] = name;
    obj["longitude"] = longitude;
    obj["latitude"] = latitude;
    obj["bearing"] = bearing;
    return obj;
  }
};

class FlightRoute : public QObject {
  Q_OBJECT
public:
  using QObject::QObject;
  void setRoutes(const QList<FPlanWPT> &routes) {
    QJsonArray array;
    for (const FPlanWPT &route : routes) {
      array.append(route.toObject());
    }
    emit routesChanged(array);
  }
signals:
  void routesChanged(const QJsonArray &);
};

#endif // FLIGHTROUTE_H

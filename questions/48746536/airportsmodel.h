#ifndef AIRPORTSMODEL_H
#define AIRPORTSMODEL_H

#include "airport.h"
#include <QAbstractListModel>
#include <QDebug>

class AirportsModel : public QAbstractListModel {
  Q_OBJECT

public:
  AirportsModel(QObject *parent = Q_NULLPTR) : QAbstractListModel(parent) {}
  enum AirportsRoles { rwRole = Qt::UserRole + 1 };

  void addAirport(const Airport &point) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_apList << point;
    endInsertRows();
  }

  Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const {
    Q_UNUSED(parent)
    return m_apList.count();
  }

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {

    if (index.row() < 0 || index.row() >= m_apList.count())
      return QVariant();
    const Airport &point = m_apList[index.row()];
    if (role == rwRole) {
      QVariantList rwCoord;
      const auto &runwayList = point.listRunways();
      for (const Runway &runwayLabeled : runwayList) {
        rwCoord << QVariant::fromValue(runwayLabeled.rwPosition());
        // qDebug() << "runway : " << runwayLabeled.nameRunway()<< " qfu : " <<
        // runwayLabeled.runwayQfu() << " coordinate : " <<
        // runwayLabeled.rwPosition();
      }
      return rwCoord; //; QVariant::fromValue(rwCoord);
    }
    return QVariant();
  }

protected:
  QHash<int, QByteArray> roleNames() const {
    QHash<int, QByteArray> roles;
    roles[rwRole] = "runways";
    return roles;
  }

private:
  QList<Airport> m_apList;
};

#endif // AIRPORTSMODEL_H

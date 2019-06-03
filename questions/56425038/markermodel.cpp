#include "markermodel.h"

MarkerModel::MarkerModel(QObject *parent)
    : QAbstractListModel(parent),
      m_maxMarkers(0)
{
}

void MarkerModel::moveMarker(const QGeoCoordinate &coordinate)
{
    QGeoCoordinate last = m_current;
    m_current = coordinate;
    Q_EMIT currentChanged();
    if(!last.isValid())
        return;
    if(m_maxMarkers == 0){
        insert(0, last);
        return;
    }
    if(rowCount() >= m_maxMarkers){
        while (rowCount() >= m_maxMarkers)
            removeLastMarker();
        removeLastMarker();
    }
    insert(0, last);
}
int MarkerModel::maxMarkers() const
{
    return m_maxMarkers;
}

void MarkerModel::setMaxMarkers(int maxMarkers)
{
    m_maxMarkers = maxMarkers > 1 ? maxMarkers: 0;
}

QGeoCoordinate MarkerModel::current() const
{
    return m_current;
}

int MarkerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_markers.count();
}

QVariant MarkerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(role == PositionRole)
        return QVariant::fromValue(m_markers[index.row()]);
    return QVariant();
}

QHash<int, QByteArray> MarkerModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PositionRole] = "position";
    return roles;
}

void MarkerModel::insert(int row, const QGeoCoordinate & coordinate)
{
    beginInsertRows(QModelIndex(), row, row);
    m_markers.insert(row, coordinate);
    endInsertRows();
}

void MarkerModel::removeLastMarker()
{
    if(m_markers.isEmpty())
        return;
    beginRemoveRows(QModelIndex(), rowCount()-1, rowCount()-1);
    m_markers.removeLast();
    endRemoveRows();
}



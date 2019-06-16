#include "coordinatemodel.h"

CoordinateModel::CoordinateModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void CoordinateModel::insert(int index, const QGeoCoordinate &coordinate){
    int i = index;
    if(index < 0) // prepend
        i = 0;
    else if (index >= rowCount()) // append
        i = rowCount();
    beginInsertRows(QModelIndex(), i, i);
    m_coordinates.insert(i, coordinate);
    endInsertRows();
}

void CoordinateModel::append(const QGeoCoordinate &coordinate){
    insert(rowCount(), coordinate);
}

void CoordinateModel::clear(){
    beginResetModel();
    m_coordinates.clear();
    endResetModel();
}

int CoordinateModel::rowCount(const QModelIndex &parent) const{
    if (parent.isValid())
        return 0;
    return m_coordinates.count();
}

QVariant CoordinateModel::data(const QModelIndex &index, int role) const{
    if (index.row() < 0 || index.row() >= m_coordinates.count())
            return QVariant();
    if (!index.isValid())
        return QVariant();
    const QGeoCoordinate &coordinate = m_coordinates[index.row()];
    if(role == PositionRole)
        return QVariant::fromValue(coordinate);
    return QVariant();
}

QHash<int, QByteArray> CoordinateModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[PositionRole] = "position";
    return roles;
}

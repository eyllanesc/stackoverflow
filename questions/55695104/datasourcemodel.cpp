#include "datasourcemodel.h"

DataSourceModel::DataSourceModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariantMap DataSourceModel::get(int row) const
{
    return m_DataSourceObjects[row].toMap();
}

void DataSourceModel::addDataSourceObject(const DataSourceObject &dataSourceObject)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_DataSourceObjects << dataSourceObject;
    endInsertRows();
}
int DataSourceModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_DataSourceObjects.count();
}

QVariant DataSourceModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_DataSourceObjects.count() || !index.isValid())
        return  QVariant();

    const DataSourceObject &dataSourceObject = m_DataSourceObjects[index.row()];
    if (role == idRole)
        return dataSourceObject.id();
    else if (role == nameRole)
        return dataSourceObject.name();
    else if (role == unitRole) {
        return dataSourceObject.unit();
    }
    else if (role == valueRole)
        return dataSourceObject.value();
    return QVariant();
}

bool DataSourceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    DataSourceObject &dataSourceObject = m_DataSourceObjects[index.row()];
    if (data(index, role) != value) {
        if(role == idRole)
            dataSourceObject.setId(value.toInt());
        else if(role == nameRole)
            dataSourceObject.setName(value.toString());
        else if(role == unitRole)
            dataSourceObject.setUnit(value.toString());
        else if(role == valueRole)
            dataSourceObject.setValue(value.toDouble());
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags DataSourceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> DataSourceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[idRole] = "id";
    roles[nameRole] = "name";
    roles[unitRole] = "unit";
    roles[valueRole] = "value";
    return  roles;
}

#ifndef MAPMARKER_H
#define MAPMARKER_H


#include <QAbstractListModel>
#include <QGeoCoordinate>
#include <QDebug>
#include <QDate>

struct gpxCoordinate {
    QGeoCoordinate latlon;
    float ele;
    QDateTime time;
};

class MarkerModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QVariantList path READ path NOTIFY pathChanged)

public:
    enum MarkerRoles{positionRole = Qt::UserRole, pathRole};

    MarkerModel(QObject *parent=nullptr): QAbstractListModel(parent)
    {
        connect(this, &QAbstractListModel::rowsInserted, this, &MarkerModel::pathChanged);
        connect(this, &QAbstractListModel::rowsRemoved, this, &MarkerModel::pathChanged);
        connect(this, &QAbstractListModel::dataChanged, this, &MarkerModel::pathChanged);
        connect(this, &QAbstractListModel::modelReset, this, &MarkerModel::pathChanged);
        connect(this, &QAbstractListModel::rowsMoved, this, &MarkerModel::pathChanged);
    }

    Q_INVOKABLE void addMarker(const QGeoCoordinate &coordinate, float elevation = 0, QDateTime dateTime = QDateTime::currentDateTime()) {

        gpxCoordinate item;
        item.latlon = coordinate;
        item.ele = elevation;
        item.time = dateTime;

        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_coordinates.append(item);
        endInsertRows();
    }



    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        if(parent.isValid()) return 0;
        return m_coordinates.count();
    }

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override {
        if(row + count > m_coordinates.count() || row < 0)
            return false;
        beginRemoveRows(parent, row, row+count-1);
        for(int i = 0; i < count; ++i)
            m_coordinates.removeAt(row + i);
        endRemoveRows();
        return true;
    }

    bool removeRow(int row, const QModelIndex &parent = QModelIndex()) {
        return removeRows(row, 1, parent);
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {

        if (index.row() < 0 || index.row() >= m_coordinates.count())
            return QVariant();
        if(role == Qt::DisplayRole)
            return QVariant::fromValue(index.row());
        else if(role == MarkerModel::positionRole){
            return QVariant::fromValue(m_coordinates[index.row()].latlon);

        }
        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override{
        QHash<int, QByteArray> roles;
        roles[positionRole] = "positionRole";
        return roles;
    }

    QVariantList path() const{
        QVariantList path;
        for(const gpxCoordinate & coord: m_coordinates){
            path << QVariant::fromValue(coord.latlon);

        }
        return path;
    }
signals:
    void pathChanged();

private:
    QVector<gpxCoordinate> m_coordinates;
};
#endif // MARKERMODEL_H

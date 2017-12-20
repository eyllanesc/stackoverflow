#ifndef NAVAIDSMODEL_H
#define NAVAIDSMODEL_H

#include "navaidspoint.h"

#include <QAbstractListModel>
#include <QFile>
#include <QTextStream>

#include <QDebug>

class NavaidsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    NavaidsModel(QObject *parent = Q_NULLPTR):QAbstractListModel(parent){
    }
    enum NavaidsRoles {
        PositionRole = Qt::UserRole + 1,
        TypeRole
    };

    void addNavaidsPoint(const NavaidsPoint &point){
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        mPoints << point;
        endInsertRows();
    }

    int rowCount(const QModelIndex & parent = QModelIndex()) const{
        Q_UNUSED(parent)
        return mPoints.count();
    }

    QVariant data(const QModelIndex & index, int role=Qt::DisplayRole) const {
        if (index.row() < 0 || index.row() >= mPoints.count())
            return QVariant();

        const NavaidsPoint &point = mPoints[index.row()];
        if (role == PositionRole)
            return QVariant::fromValue(point.position());
        if (role == TypeRole){
            return QVariant::fromValue(point.type());
        }
        return QVariant();
    }

protected:
    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles[PositionRole] = "position";
        roles[TypeRole] = "type";
        return roles;
    }
private:
    QList<NavaidsPoint> mPoints;
};

#endif // NAVAIDSMODEL_H

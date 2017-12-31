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
        OACICodeRole,
        CountryCodeRole
    };

    void readFromCSV(const QString &filename){
        QFile file(filename);
        if(!file.open(QFile::ReadOnly | QFile::Text))
            return;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList elements = line.split(",");
            if(elements.count()==4){
                QString code = elements[0];
                double latitude = elements[1].toDouble();
                double longitude = elements[2].toDouble();
                QString country = elements[3];
                NavaidsPoint p(code, latitude, longitude, country);
                addNavaidsPoint(p);
            }
        }
    }

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
        else if (role == OACICodeRole)
            return point.oaciCode();
        else if (role == CountryCodeRole)
            return point.countryCode();
        return QVariant();
    }

protected:
    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles[PositionRole] = "position";
        roles[OACICodeRole] = "oaci";
        roles[CountryCodeRole] = "country";
        return roles;
    }
private:
    QList<NavaidsPoint> mPoints;
};

#endif // NAVAIDSMODEL_H

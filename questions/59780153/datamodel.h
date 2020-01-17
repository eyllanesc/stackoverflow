#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractListModel>
#include <QGeoCoordinate>
#include <QTimer>
#include <random>

#include <QDebug>

struct Data{
    QGeoCoordinate position;
    QGeoCoordinate nextposition;
};

static QGeoCoordinate osloposition(59.91, 10.75); // Oslo;

class DataModel : public QAbstractListModel
{
    Q_OBJECT
    QList<Data> m_datas;
public:
    enum PositionRoles {
        PositionRole = Qt::UserRole + 1,
        NextPositionRole
    };
    explicit DataModel(QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
        init();
    }
    int rowCount(const QModelIndex &parent = QModelIndex()) const override{
        return parent.isValid() ? 0: m_datas.count();
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override{
        if (!index.isValid() || index.row() < 0 || index.row() >= m_datas.count())
            return QVariant();
        const Data &data = m_datas[index.row()];
        if (role == PositionRole)
            return QVariant::fromValue(data.position);
        else if (role == NextPositionRole)
            return QVariant::fromValue(data.nextposition);
        return QVariant();
    }
    QHash<int, QByteArray> roleNames() const override{
        QHash<int, QByteArray> roles;
        roles[PositionRole] = "position";
        roles[NextPositionRole] = "nextposition";
        return roles;
    }
private:
    void init(){
        for(int i=0; i< 10; ++i){
            Data data;
            data.position = osloposition;;
            data.nextposition = data.position;
            m_datas << data;
        }
        QTimer *timer = new QTimer(this);
        QObject::connect(timer, &QTimer::timeout, this, &DataModel::updateData);
        timer->start(60 * 1000);
        updateData();
    }
    void updateData(){
        qDebug() << __PRETTY_FUNCTION__;
        static std::default_random_engine e;
        static std::uniform_real_distribution<> dis(-.1, .1);
        for(int i=0; i < m_datas.count(); ++i){
            Data & data = m_datas[i];
            QModelIndex ix = index(i);
            data.position = data.nextposition;
            data.nextposition = QGeoCoordinate(osloposition.latitude() + dis(e),
                                           osloposition.longitude() + dis(e));
            Q_EMIT dataChanged(ix, ix, {PositionRole, NextPositionRole});
        }
    }
};

#endif // DATAMODEL_H

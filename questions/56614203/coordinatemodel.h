#ifndef COORDINATEMODEL_H
#define COORDINATEMODEL_H

#include <QAbstractListModel>
#include <QGeoCoordinate>

class CoordinateModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum{
        PositionRole = Qt::UserRole + 1000
    };
    explicit CoordinateModel(QObject *parent = nullptr);

    void insert(int index, const QGeoCoordinate & coordinate);
    void append(const QGeoCoordinate & coordinate);
    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<QGeoCoordinate> m_coordinates;
};

#endif // COORDINATEMODEL_H

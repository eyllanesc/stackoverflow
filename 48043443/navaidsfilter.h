#ifndef NAVAIDSFILTER_H
#define NAVAIDSFILTER_H

#include "navaidsmodel.h"

#include <QSortFilterProxyModel>
#include <QRegularExpression>

#include <QDebug>

class NavaidsFilter : public QSortFilterProxyModel
{
public:
    NavaidsFilter(QObject *parent = Q_NULLPTR):QSortFilterProxyModel(parent){}
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const{

        QRegularExpression rx("ROBU");

        QModelIndex ix = sourceModel()->index(source_row, 0, source_parent);
        QGeoCoordinate pos = ix.data(NavaidsModel::PositionRole).value<QGeoCoordinate>();
        QString code = ix.data(NavaidsModel::OACICodeRole).toString();
        QString country = ix.data(NavaidsModel::CountryCodeRole).toString();

        qDebug()<<pos<<code<<country;

        if(code.contains(rx)){
            return true;
        }
        return false;
    }
};

#endif // NAVAIDSFILTER_H

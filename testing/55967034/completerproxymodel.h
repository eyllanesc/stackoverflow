#ifndef COMPLETERPROXYMODEL_H
#define COMPLETERPROXYMODEL_H

#include <QSortFilterProxyModel>

class CompleterProxyModel : public QSortFilterProxyModel
{
public:
    using QSortFilterProxyModel::QSortFilterProxyModel;
protected:
    bool lessThan( const QModelIndex &p_left, const QModelIndex &p_right ) const override;
};

#endif // COMPLETERPROXYMODEL_H

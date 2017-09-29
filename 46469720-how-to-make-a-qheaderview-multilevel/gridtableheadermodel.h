#ifndef GRIDTABLEHEADERMODEL_H
#define GRIDTABLEHEADERMODEL_H

#include "tableheaderitem.h"

#include <QAbstractTableModel>

class GridTableHeaderModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum HeaderRole
    {
        ColumnSpanRole = Qt::UserRole+1,
        RowSpanRole,
    };

    GridTableHeaderModel(int row, int column, QObject *parent=0);
    ~GridTableHeaderModel();

    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
private:
    int _row;
    int _column;
    TableHeaderItem *rootItem;
};

#endif // GRIDTABLEHEADERMODEL_H

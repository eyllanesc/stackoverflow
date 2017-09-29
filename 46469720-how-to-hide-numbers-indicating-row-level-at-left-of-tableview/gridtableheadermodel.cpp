#include "gridtableheadermodel.h"

#include <QAbstractTableModel>

GridTableHeaderModel::GridTableHeaderModel(int row, int column, QObject *parent)
    :QAbstractTableModel(parent), _row(row), _column(column), rootItem(new TableHeaderItem)
{

}
GridTableHeaderModel::~GridTableHeaderModel(){
    rootItem->clear();
    delete rootItem;
}

QModelIndex GridTableHeaderModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();
    TableHeaderItem *parentItem;
    if(!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TableHeaderItem *>(parent.internalPointer());

    TableHeaderItem *childItem = parentItem->child(row, column);
    if(!childItem)
        childItem = parentItem->insertChild(row, column);
    return createIndex(row, column, childItem);
}

int GridTableHeaderModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _row;
}

int GridTableHeaderModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return _column;
}

Qt::ItemFlags GridTableHeaderModel::flags(const QModelIndex &index) const{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return QAbstractTableModel::flags(index);
}

QVariant GridTableHeaderModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
        return QVariant();
    if(index.row() >= _row || index.row() < 0|| index.column() >= _column || index.column() < 0)
        return QVariant();
    TableHeaderItem *item = static_cast<TableHeaderItem *>(index.internalPointer());
    return item->data(role);
}

bool GridTableHeaderModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(index.isValid()){
        TableHeaderItem *item = static_cast<TableHeaderItem *>(index.internalPointer());
        if(role == ColumnSpanRole){
            int col = index.column();
            int span = value.toInt();
            if(span > 0){
                if(col+span-1 >= _column)
                    span = _column - col;
                item->setData(span, ColumnSpanRole);
            }
        }
        else if(role == RowSpanRole){
            int row = index.row();
            int span = value.toInt();
            if (span > 0){
                if(row+span-1 > _row)
                    span = _column - row;
                item->setData(span, RowSpanRole);
            }
        }
        else
            item->setData(value, role);
        return true;
    }
    return false;
}

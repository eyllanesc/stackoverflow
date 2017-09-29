#include "tableheaderitem.h"

TableHeaderItem::TableHeaderItem(TableHeaderItem *parent){
    TableHeaderItem(0, 0, parent);
}

TableHeaderItem::TableHeaderItem(int row, int column, TableHeaderItem *parent):
    m_parentItem(parent), _row(row), _column(column)
{}

TableHeaderItem *TableHeaderItem::insertChild(int row, int col){
    TableHeaderItem *child = new TableHeaderItem(row, col, this);
    m_childItems.insert(QPair<int, int>(row, col), child);
    return child;
}

TableHeaderItem *TableHeaderItem::child(int row, int col){
    QHash<QPair<int,int>,TableHeaderItem*>::iterator it = m_childItems.find(QPair<int, int>(row, col));
    if(it != m_childItems.end())
        return it.value();
    return 0;
}

TableHeaderItem *TableHeaderItem::parent(){
    return m_parentItem;
}

int TableHeaderItem::row() const{
    return _row;
}

int TableHeaderItem::column() const{
    return _column;
}

void TableHeaderItem::setData(const QVariant &data, int role){
    m_itemData.insert(role, data);
}

QVariant TableHeaderItem::data(int role) const{
    QHash<int,QVariant>::const_iterator it = m_itemData.find(role);
    if (it != m_itemData.end())
        return it.value();
    return QVariant();
}

void TableHeaderItem::clear(){
    for(TableHeaderItem* item: m_childItems){
        item->clear();
        if (item) delete item;
    }
    m_childItems.clear();
}

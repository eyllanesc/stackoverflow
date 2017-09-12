#include "sqltablemodel.h"

#include <QBrush>
#include <QSqlQuery>
#include <QSqlTableModel>

#define id_col 0
#define position_col 1
#define state_col 2

int SqlTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return max_position + 1;;
}

void SqlTableModel::setTable(const QString &tableName)
{
    QSqlQuery q(QString("SELECT MAX(position) FROM %1").arg(tableName));
    while (q.next()) {
        max_position  = q.value(id_col).toInt();
    }
    QSqlTableModel::setTable(tableName);
}

QVariant SqlTableModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::ForegroundRole){
        return QBrush(Qt::black);
    }
    if(index.column()>0){
        if(role==Qt::DisplayRole){
            int position = QSqlTableModel::data(this->index(index.row(), position_col), Qt::DisplayRole).toInt();
            if(index.column() == position){
                return QSqlTableModel::data(this->index(index.row(), state_col), Qt::DisplayRole).toString();
            }
        }
        return QVariant();
    }
    return QSqlTableModel::data(index, role);
}

QVariant SqlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if(orientation == Qt::Horizontal && role == Qt::DisplayRole && section > 0)
        return section;

    return QSqlTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags SqlTableModel::flags(const QModelIndex &index) const
{
    int position = QSqlTableModel::data(this->index(index.row(), position_col), Qt::DisplayRole).toInt();
    /*if(index.column() == 0)
        return QSqlTableModel::flags(index);*/
    if(index.column() == position){
        return QSqlTableModel::flags(this->index(index.row(), id_col));
    }
    return Qt::NoItemFlags;
}

bool SqlTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role==Qt::EditRole){
        int position = QSqlTableModel::data(this->index(index.row(), position_col), Qt::DisplayRole).toInt();
        if(index.column() == position){
            QSqlQuery q;
            int id = QSqlTableModel::data(this->index(index.row(), id_col), Qt::DisplayRole).toInt();
            q.exec(QString("UPDATE %1 SET state = '%2' WHERE id =%3")
                   .arg(tableName())
                   .arg(value.toString())
                   .arg(id));
            select();
            return true;
        }
    }
    return QSqlTableModel::setData(index, value, role);
}

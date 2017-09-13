#include "sqltablemodel.h"

#include <QBrush>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>

int SqlTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return max_position + 1;;
}

void SqlTableModel::setTable(const QString &tableName)
{
    QSqlQuery q;
    q.exec(QString("PRAGMA table_info(%1)").arg(tableName));
    while (q.next()) {
        if(q.value(1).toString() == positionName)
            index_position = q.at();
        if(q.value(1).toString() == stateName)
            index_state = q.at();
    }

    q.exec(QString("SELECT MAX(position) FROM %1").arg(tableName));
    while (q.next()) {
        max_position  = q.value(0).toInt();
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
            int position = QSqlTableModel::data(this->index(index.row(), index_position), Qt::DisplayRole).toInt();
            if(index.column() == position){
                return QSqlTableModel::data(this->index(index.row(), index_state), Qt::DisplayRole).toString();
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
    int position = QSqlTableModel::data(this->index(index.row(), index_position), Qt::DisplayRole).toInt();

    /*if(QSqlTableModel::data(this->index(index.row(), index_state), Qt::DisplayRole).toString().isEmpty()){
        return QSqlTableModel::flags(this->index(index.row(), 0));
    }*/
    if(index.column() == position){
        return QSqlTableModel::flags(this->index(index.row(), 0));
    }
    return Qt::NoItemFlags;
}

bool SqlTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role==Qt::EditRole){
        int position = QSqlTableModel::data(this->index(index.row(), index_position), Qt::DisplayRole).toInt();
        if(index.column() == position){
            QSqlQuery q;
            int id = QSqlTableModel::data(this->index(index.row(), 0), Qt::DisplayRole).toInt();
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

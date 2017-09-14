#include "sqltablemodel.h"

#include <QBrush>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>

#include <QDebug>

int SqlTableModel::columnCount(const QModelIndex &parent) const
{
    return QSqlTableModel::columnCount(parent)+ max_position;;
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
    const int number_of_columns = QSqlTableModel::columnCount();
    if(index.column()>= number_of_columns){
        if(role==Qt::DisplayRole){
            int position = QSqlTableModel::data(this->index(index.row(), index_position), Qt::DisplayRole).toInt();
            if(index.column() == number_of_columns + position - 1){
                return QSqlTableModel::data(this->index(index.row(), index_state), Qt::DisplayRole).toString();
            }
        }
    }
    return QSqlTableModel::data(index, role);
}

QVariant SqlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole && section >= QSqlTableModel::columnCount())
        return section -  QSqlTableModel::columnCount() + 1;
    return QSqlTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags SqlTableModel::flags(const QModelIndex &index) const
{
    if(index.column() >= QSqlTableModel::columnCount()){
        return Qt::ItemIsSelectable| Qt::ItemIsEditable| Qt::ItemIsEnabled;
    }
    return QSqlTableModel::flags(index);
}

bool SqlTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role==Qt::EditRole){
        const int number_of_columns =  QSqlTableModel::columnCount();
        if(index.column() >= number_of_columns){
            QSqlQuery q;
            int id = QSqlTableModel::data(this->index(index.row(), 0), Qt::DisplayRole).toInt();
            q.prepare(QString("UPDATE %1 SET %2 = :state, %3=:position WHERE id =:id")
                      .arg(tableName())
                      .arg(stateName)
                      .arg(positionName));
            q.bindValue(":state", value);
            q.bindValue(":position", index.column()-number_of_columns +1);
            q.bindValue(":id", id);
            q.exec();
            select();
            return true;
        }
    }
    return QSqlTableModel::setData(index, value, role);
}

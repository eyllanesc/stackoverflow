#include "sqltablemodel.h"

#include <QBrush>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTimer>


int SqlTableModel::columnCount(const QModelIndex &parent) const
{
    return QSqlTableModel::columnCount(parent)+ max_position;;
}

void SqlTableModel::setTable(const QString &tableName)
{

    QSqlTableModel::setTable(tableName);

    index_position = fieldIndex(positionName);
    index_state = fieldIndex(stateName);
    reset();
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
            bool result1 = QSqlTableModel::setData(this->index(index.row(), index_position), index.column()-number_of_columns +1, role);
            bool result2 = QSqlTableModel::setData(this->index(index.row(), index_state), value, role);

            return result1 && result2;
        }
        if(index.column() == index_position){
            QTimer::singleShot(0, this, &SqlTableModel::reset);
        }
    }

    return QSqlTableModel::setData(index, value, role);
}

void SqlTableModel::reset()
{
    QSqlQuery q;
    q.exec(QString("SELECT MAX(%1) FROM %2").arg(positionName).arg(tableName()));
    int val;
    while (q.next()) {
        val = q.value(0).toInt();
    }

    if(val != max_position){
        beginResetModel();
        max_position = val;
        endResetModel();
    }
}

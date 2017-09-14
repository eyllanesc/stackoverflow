#ifndef SQLTABLEMODEL_H
#define SQLTABLEMODEL_H

#include <QSqlTableModel>

class SqlTableModel : public QSqlTableModel
{
    const QString stateName = "state";
    const QString positionName = "position";

public:
    int	columnCount(const QModelIndex &parent = QModelIndex()) const;
    void setTable(const QString &tableName);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

   bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
private:
    int max_position;

    int index_position;
    int index_state;

    void reset();
};

#endif // SQLTABLEMODEL_H

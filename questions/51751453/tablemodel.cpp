#include "tablemodel.h"

TableModel::TableModel(int rows, int columns, QObject *parent)
    : QAbstractTableModel(parent) {
  QList<Item> newList;

  for (int column = 0; column < qMax(1, columns); ++column) {
    newList.append(Item{});
  }

  for (int row = 0; row < qMax(1, rows); ++row) {
    m_items.append(newList);
  }
}

int TableModel::rowCount(const QModelIndex & /*parent*/) const {
  return m_items.size();
}

int TableModel::columnCount(const QModelIndex & /*parent*/) const {
  return m_items[0].size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();
  const Item &item = m_items[index.row()][index.column()];
  if (role == Qt::DisplayRole)
    return item.text;
  else if (role == Qt::ForegroundRole) {
    return item.textColor;
  } else if (role == Qt::BackgroundRole) {
    return item.bgColor;
  } else
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation,
                                int role) const {
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal)
    return QString("Column %1").arg(section);
  else
    return QString("Row %1").arg(section);
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value,
                         int role) {
  if (!index.isValid())
    return false;
  Item &item = m_items[index.row()][index.column()];
  if (role == Qt::EditRole || role == Qt::DisplayRole) {
    item.text = value.toString();
  } else if (role == Qt::ForegroundRole) {
    if (value.canConvert<QBrush>())
      item.textColor = value.value<QBrush>();
  } else if (role == Qt::BackgroundRole) {
    if (value.canConvert<QBrush>())
      item.bgColor = value.value<QBrush>();
  } else
    return false;
  emit dataChanged(index, index);
  return true;
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &parent) {
  int columns = columnCount();
  beginInsertRows(parent, position, position + rows - 1);

  for (int row = 0; row < rows; ++row) {
    QList<Item> items;
    for (int column = 0; column < columns; ++column)
      items.append(Item{});
    m_items.insert(position, items);
  }

  endInsertRows();
  return true;
}

bool TableModel::insertColumns(int position, int columns,
                               const QModelIndex &parent) {
  int rows = rowCount();
  beginInsertColumns(parent, position, position + columns - 1);
  for (int row = 0; row < rows; ++row) {
    for (int column = position; column < columns; ++column) {
      m_items[row].insert(position, Item{});
    }
  }
  endInsertColumns();
  return true;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &parent) {
  beginRemoveRows(parent, position, position + rows - 1);
  for (int row = 0; row < rows; ++row) {
    m_items.removeAt(position);
  }
  endRemoveRows();
  return true;
}

bool TableModel::removeColumns(int position, int columns,
                               const QModelIndex &parent) {
  int rows = rowCount();
  beginRemoveColumns(parent, position, position + columns - 1);
  for (int row = 0; row < rows; ++row) {
    for (int column = 0; column < columns; ++column) {
      m_items[row].removeAt(position);
    }
  }
  endRemoveColumns();
  return true;
}

#include "QDataItem.h"

QDataItem::QDataItem(const QList<QVariant> &data, QDataItem *parentItem) {
  m_text = data[0].toString();
  m_parentItem = parentItem;
  m_itemData = data;
}

QDataItem::~QDataItem() { qDeleteAll(m_childItems); }

void QDataItem::appendChild(QDataItem *child) { m_childItems.append(child); }

QDataItem *QDataItem::child(int row) { return m_childItems.value(row); }

int QDataItem::childCount() const { return m_childItems.count(); }

int QDataItem::columnCount() const { return m_itemData.count(); }

QVariant QDataItem::data(int column) const { return m_itemData.value(column); }

int QDataItem::row() const {
  if (m_parentItem)
    return m_parentItem->m_childItems.indexOf(const_cast<QDataItem *>(this));
  return 0;
}

QDataItem *QDataItem::parentItem() { return m_parentItem; }

QString QDataItem::getText() { return m_text; }

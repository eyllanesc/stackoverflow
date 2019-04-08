#ifndef QDataItem_H
#define QDataItem_H

#include <QVariant>

class QDataItem {
public:
  explicit QDataItem(const QList<QVariant> &data, QDataItem *parentItem = 0);
  ~QDataItem();
  void appendChild(QDataItem *child);
  QDataItem *child(int row);
  int childCount() const;
  int columnCount() const;
  QVariant data(int column) const;
  int row() const;
  QDataItem *parentItem();
  QString getText();

private:
  QList<QDataItem *> m_childItems;
  QList<QVariant> m_itemData;
  QDataItem *m_parentItem;
  QString m_text;
};

#endif // QDataItem_H

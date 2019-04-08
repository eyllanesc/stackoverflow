#ifndef USERITEMDELEGATE_H
#define USERITEMDELEGATE_H

#include <QStyledItemDelegate>

class UserItemDelegate : public QStyledItemDelegate {
public:
  using QStyledItemDelegate::QStyledItemDelegate;
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override;
};

#endif // USERITEMDELEGATE_H

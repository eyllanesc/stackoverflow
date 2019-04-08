#include "useritemdelegate.h"
#include "userentrywidget.h"
#include "userinfo.h"

#include <QDebug>

QWidget *UserItemDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const {
  if (index.data().canConvert<UserInfo>()) {
    auto editor = new UserEntryWidget(parent);
    return editor;
  } else {
    return QStyledItemDelegate::createEditor(parent, option, index);
  }
}

void UserItemDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const {
  if (index.data().canConvert<UserInfo>()) {
    UserInfo user = qvariant_cast<UserInfo>(index.data());
    UserEntryWidget *userEditor = qobject_cast<UserEntryWidget *>(editor);
    userEditor->setUserInfo(user);
    qDebug() << userEditor;
  } else {
    QStyledItemDelegate::setEditorData(editor, index);
  }
}

QSize UserItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const {
  return QSize(100, 100);
}

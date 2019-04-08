#include "userinfo.h"
#include "useritemdelegate.h"
#include "userlistmodel.h"

#include <QApplication>
#include <QDebug>
#include <QListView>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  qRegisterMetaType<UserInfo>("UserInfo");
  qDebug() << QMetaType::type("UserInfo");

  auto lm = new UserListModel();
  lm->insertRows(0, 5);

  auto widget = new QListView();
  widget->setModel(lm);

  widget->setItemDelegate(new UserItemDelegate());
  for (int i = 0; i < 5; i++) {
    widget->openPersistentEditor(lm->index(i, 0));
  }

  widget->resize(500, 300);
  widget->show();

  return a.exec();
}

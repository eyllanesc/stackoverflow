#ifndef USERENTRYWIDGET_H
#define USERENTRYWIDGET_H

#include "userinfo.h"

#include <QWidget>
class QLabel;

class UserEntryWidget : public QWidget {
  Q_OBJECT
public:
  explicit UserEntryWidget(QWidget *parent = nullptr);
  void setUserInfo(const UserInfo &user);

private:
  QLabel *avatar, *title, *subtitle, *time;
};
#endif // USERENTRYWIDGET_H

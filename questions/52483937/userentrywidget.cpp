#include "userentrywidget.h"

#include <QHBoxLayout>
#include <QLabel>

UserEntryWidget::UserEntryWidget(QWidget *parent) : QWidget(parent) {
  avatar = new QLabel();
  title = new QLabel("title");
  subtitle = new QLabel("subtitle");
  time = new QLabel("00:00");
  auto layout = new QHBoxLayout(this);
  layout->addWidget(avatar);
  auto centralColumn = new QVBoxLayout();
  centralColumn->addWidget(title);
  centralColumn->addWidget(subtitle);
  layout->addLayout(centralColumn);
  layout->addWidget(time);
  setFixedHeight(sizeHint().height());
}

void UserEntryWidget::setUserInfo(const UserInfo &user) {
  avatar->setPixmap(QPixmap::fromImage(user.getAvatar()));
  title->setText(user.getTitle());
  subtitle->setText(user.getSubtitle());
  time->setText(user.getTime().toString("hh:mm"));
}

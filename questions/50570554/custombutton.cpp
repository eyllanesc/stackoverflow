#include "custombutton.h"

#include <QVBoxLayout>

CustomButton::CustomButton(QWidget *parent) : QPushButton(parent) {
  move(10, 20);
  setCursor(Qt::PointingHandCursor);
  right.setFixedWidth(50);

  left.setText("Left");
  right.setText("Right");

  left.setAlignment(Qt::AlignCenter);
  right.setAlignment(Qt::AlignCenter);

  QHBoxLayout *hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);

  hlay->addWidget(&left);
  hlay->addWidget(&right);

  left.setStyleSheet(leftqss);
  right.setStyleSheet(rightqss);

  // left.adjustSize();
}

void CustomButton::enterEvent(QEvent *event) {
  left.setStyleSheet(rightqss);
  right.setStyleSheet(leftqss);
  QPushButton::enterEvent(event);
}

void CustomButton::leaveEvent(QEvent *event) {
  left.setStyleSheet(leftqss);
  right.setStyleSheet(rightqss);
  QPushButton::leaveEvent(event);
}

#include "passwordlineedit.h"

PasswordLineEdit::PasswordLineEdit(QWidget *parent) : QLineEdit(parent) {
  setEchoMode(QLineEdit::Password);
  QAction *action = addAction(QIcon(":/eyeOff"), QLineEdit::TrailingPosition);
  button = qobject_cast<QToolButton *>(action->associatedWidgets().last());
  button->hide();
  button->setCursor(QCursor(Qt::PointingHandCursor));
  connect(button, &QToolButton::pressed, this, &PasswordLineEdit::onPressed);
  connect(button, &QToolButton::released, this, &PasswordLineEdit::onReleased);
}

void PasswordLineEdit::onPressed() {
  QToolButton *button = qobject_cast<QToolButton *>(sender());
  button->setIcon(QIcon(":/eyeOn"));
  setEchoMode(QLineEdit::Normal);
}

void PasswordLineEdit::onReleased() {
  QToolButton *button = qobject_cast<QToolButton *>(sender());
  button->setIcon(QIcon(":/eyeOff"));
  setEchoMode(QLineEdit::Password);
}

void PasswordLineEdit::enterEvent(QEvent *event) {
  button->show();
  QLineEdit::enterEvent(event);
}

void PasswordLineEdit::leaveEvent(QEvent *event) {
  button->hide();
  QLineEdit::leaveEvent(event);
}

void PasswordLineEdit::focusInEvent(QFocusEvent *event) {
  button->show();
  QLineEdit::focusInEvent(event);
}

void PasswordLineEdit::focusOutEvent(QFocusEvent *event) {
  button->hide();
  QLineEdit::focusOutEvent(event);
}

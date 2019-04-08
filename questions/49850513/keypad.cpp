#include "keypad.h"

#include <QApplication>
#include <QCoreApplication>
#include <QGridLayout>
#include <QKeyEvent>
#include <QToolButton>

Keypad::Keypad(QWidget *parent) : QWidget{parent} {
  QGridLayout *lay = new QGridLayout{this};
  const std::vector<Keys> keys = {
      {"1", Qt::Key_1},     {"2", Qt::Key_2},        {"3", Qt::Key_3},
      {"4", Qt::Key_4},     {"5", Qt::Key_5},        {"6", Qt::Key_6},
      {"7", Qt::Key_7},     {"8", Qt::Key_8},        {"9", Qt::Key_9},
      {".", Qt::Key_Colon}, {"del", Qt::Key_Delete}, {"enter", Qt::Key_Return}};

  for (unsigned int i = 0; i < keys.size(); i++) {
    QToolButton *button = new QToolButton;
    button->setFixedSize(64, 64);
    const Keys &_key = keys[i];
    button->setText(_key.name);
    lay->addWidget(button, i / 3, i % 3);
    button->setProperty("key", _key.key);
    connect(button, &QToolButton::clicked, this, &Keypad::on_clicked);
  }
}

void Keypad::on_clicked() {
  QToolButton *button = qobject_cast<QToolButton *>(sender());
  const QString &text = button->text();
  int key = button->property("key").toInt();
  QWidget *widget = QApplication::focusWidget();

  if (text == "del") {
    QKeyEvent *event =
        new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::ControlModifier, text);
    QCoreApplication::postEvent(widget, event);
  }
  QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier, text);
  QCoreApplication::postEvent(widget, event);
}

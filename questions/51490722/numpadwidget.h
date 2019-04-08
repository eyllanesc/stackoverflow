#ifndef NUMPADWIDGET_H
#define NUMPADWIDGET_H

#include <QApplication>
#include <QGridLayout>
#include <QKeyEvent>
#include <QToolButton>
#include <QWidget>

class NumpadWidget : public QWidget {
  Q_OBJECT
public:
  explicit NumpadWidget(QWidget *parent = nullptr) : QWidget(parent) {
    QGridLayout *lay = new QGridLayout(this);

    const std::vector<QPair<QString, int>> values{
        {"1", Qt::Key_1},     {"2", Qt::Key_2}, {"3", Qt::Key_3},
        {"4", Qt::Key_4},     {"5", Qt::Key_5}, {"6", Qt::Key_6},
        {"7", Qt::Key_7},     {"8", Qt::Key_8}, {"9", Qt::Key_9},
        {".", Qt::Key_Colon}, {"0", Qt::Key_0}, {"*", Qt::Key_Asterisk}};

    int i = 0;
    int j = 0;

    for (const QPair<QString, int> &value : values) {
      QToolButton *button = new QToolButton;
      button->setText(value.first);
      button->setFixedSize(40, 40);
      lay->addWidget(button, i, j);
      button->setProperty("text", value.first);
      button->setProperty("key", value.second);
      connect(button, &QToolButton::clicked, this, &NumpadWidget::onClicked);
      j++;
      if (j % 3 == 0) {
        j = 0;
        i++;
      }
    }
    setFixedSize(sizeHint());
  }
private slots:
  void onClicked() {
    if (QWidget *widget = QApplication::focusWidget()) {
      QString text = sender()->property("text").toString();
      int key = sender()->property("key").toInt();
      QKeyEvent *event =
          new QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier, text);
      QCoreApplication::postEvent(widget, event);
    }
  }
};

#endif // NUMPADWIDGET_H

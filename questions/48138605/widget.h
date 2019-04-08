#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QVBoxLayout;
class QComboBox;
class QLabel;

namespace Ui {
class Widget;
}

class Widget : public QWidget {
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

private slots:
  void on_horizontalSlider_valueChanged(int value);

private:
  Ui::Widget *ui;
  QList<QWidget *> widget;
  QList<QVBoxLayout *> layout;
  QList<QComboBox *> box;
  QList<QLabel *> pic;
};

#endif // WIDGET_H

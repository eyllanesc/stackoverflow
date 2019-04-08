#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QWidget>

namespace Ui {
class CustomSlider;
}

class CustomSlider : public QWidget {
  Q_OBJECT

public:
  explicit CustomSlider(QWidget *parent = 0);
  ~CustomSlider();

  bool eventFilter(QObject *obj, QEvent *ev);

private:
  Ui::CustomSlider *ui;
  void changeSliderValue();
  int lastSaved;
};

#endif // CUSTOMSLIDER_H

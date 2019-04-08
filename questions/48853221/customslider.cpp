#include "customslider.h"
#include "ui_customslider.h"

#include <QEvent>
#include <QSlider>

CustomSlider::CustomSlider(QWidget *parent)
    : QWidget(parent), ui(new Ui::CustomSlider) {
  ui->setupUi(this);
  ui->horizontalSlider->installEventFilter(this);
  ui->horizontalSlider->setMaximum(1);
}

CustomSlider::~CustomSlider() { delete ui; }

bool CustomSlider::eventFilter(QObject *obj, QEvent *ev) {
  if (ev->type() == QEvent::MouseButtonRelease) {
    changeSliderValue();
  }
  if (ev->type() == QEvent::MouseButtonPress) {
    lastSaved = ui->horizontalSlider->value();
  }
  return QWidget::eventFilter(obj, ev);
}

void CustomSlider::changeSliderValue() {
  int current = ui->horizontalSlider->value();
  if (lastSaved == current) {
    ui->horizontalSlider->setValue(current == 1 ? 0 : 1);
  }
}

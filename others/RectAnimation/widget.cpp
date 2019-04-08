#include "widget.h"

#include <QPainter>
#include <QPropertyAnimation>

Widget::Widget(QWidget *parent) : QWidget(parent) {

  QPropertyAnimation *animation = new QPropertyAnimation(this, "nrect");
  // animation->setEasingCurve(QEasingCurve::InBack);
  animation->setDuration(10000);
  animation->setStartValue(QRect(0, 0, 10, 10));
  animation->setEndValue(QRect(0, 0, 200, 200));
  animation->start();
  connect(animation, &QPropertyAnimation::valueChanged, [=]() { update(); });
}

Widget::~Widget() {}

QRect Widget::nRect() const { return mRect; }

void Widget::setNRect(const QRect &rect) { mRect = rect; }

void Widget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)
  QRect ellipse(mRect);
  QPainter painter(this);
  painter.setBrush(Qt::red);
  painter.drawEllipse(ellipse);
}

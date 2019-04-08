#include "mycircle.h"

MyCircle::MyCircle(QObject *parent) : QObject(parent) {
  rect = QRect(0, 0, 100, 100);
}

QRect MyCircle::geometry() const { return rect; }

void MyCircle::setGeometry(const QRect &value) {
  if (rect != value) {
    rect = value;
    update();
  }
}

QRectF MyCircle::boundingRect() const { return QRectF(rect); }

void MyCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->setBrush(QBrush(Qt::red));
  painter->drawEllipse(rect);
}

#include "mygraphicsrectitem.h"

MyGraphicsRectItem::MyGraphicsRectItem(qreal x, qreal y, qreal width,
                                       qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, width, height, parent) {
  setAcceptHoverEvents(true);
}

MyGraphicsRectItem::MyGraphicsRectItem(QObject *parent) : QObject(parent) {

  setAcceptHoverEvents(true);
}

QPointF MyGraphicsRectItem::position() const { return pos(); }

void MyGraphicsRectItem::setPosition(const QPointF &position) {
  setPos(position);
}

QRectF MyGraphicsRectItem::geometry() const { return rect(); }

void MyGraphicsRectItem::setGeometry(const QRectF &geometry) {
  setRect(geometry);
}

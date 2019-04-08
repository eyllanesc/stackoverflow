#include "block.h"

#include <QPainter>

class QGraphicsSceneMouseEvent;
Block::Block(QGraphicsItem *parent) : QGraphicsPathItem(parent) {
  QPainterPath p;
  //<->,|,<->,|,roundness
  p.addRoundedRect(0, 0, 80, 50, 5, 5);
  setPath(p);
  setAcceptDrops(true);
  setAcceptedMouseButtons(Qt::LeftButton);
}
void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
  Q_UNUSED(option)
  Q_UNUSED(widget)
  painter->setPen(QPen(QColor(67, 141, 220)));
  painter->setBrush(QColor(67, 141, 220, 100));
  painter->drawPath(path());
}

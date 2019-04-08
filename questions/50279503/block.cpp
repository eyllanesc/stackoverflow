#include "block.h"

#include <QPen>

Block::Block(QString color, QGraphicsItem *parent) : QGraphicsPathItem(parent) {
  QPainterPath p;
  p.addRoundedRect(0, 0, 150, 50, 2, 2);
  setPath(p);
  setPen(QPen(Qt::black));
  setBrush(QColor(color.toLower()));
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
}

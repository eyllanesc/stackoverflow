#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsPathItem>
class QGraphicsSceneMouseEvent;
class Block : public QGraphicsPathItem {
public:
  enum { Type = QGraphicsItem::UserType + 3 };
  int type() const { return Type; }
  Block(QGraphicsItem *parent = 0);
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
};

#endif // BLOCK_H

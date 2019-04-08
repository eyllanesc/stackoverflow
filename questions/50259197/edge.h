#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem {
public:
  Edge(Node *sourceNode, Node *destNode);
  virtual ~Edge();
  const uint id;
  Node *sourceNode() const;
  Node *destNode() const;

  void adjust();

  enum { Type = UserType + 2 };
  int type() const override { return Type; }

protected:
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

private:
  Node *source, *dest;
  QPointF sourcePoint;
  QPointF destPoint;
  qreal arrowSize;
  static uint _idStatic;
};

#endif // EDGE_H

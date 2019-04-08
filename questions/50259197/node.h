#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class Node : public QGraphicsItem {
public:
  static const QPen _pen;
  Node(GraphWidget *graphWidget);
  virtual ~Node();
  const uint id;
  void addEdge(Edge *edge);
  QList<Edge *> edges() const;

  enum { Type = UserType + 1 };
  int type() const override { return Type; }
  enum { Radius = 30 };

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  static uint idStatic();
  void removeEdge(Edge *edge);

protected:
  QVariant itemChange(GraphicsItemChange change,
                      const QVariant &value) override;

private:
  QList<Edge *> edgeList;
  QPointF newPos;
  GraphWidget *graph;
  static uint _idStatic;
};

#endif // NODE_H

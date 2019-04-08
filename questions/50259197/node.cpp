#include "node.h"
#include "edge.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

const QPen Node::_pen = QPen(Qt::black, 2);
uint Node::_idStatic = 0;

Node::Node(GraphWidget *graphWidget) : id(_idStatic++), graph(graphWidget) {
  setFlag(ItemIsSelectable);
  setFlag(ItemIsMovable);
  setFlag(ItemSendsGeometryChanges);
  setCacheMode(DeviceCoordinateCache);
  setZValue(1);
}

Node::~Node() {
  foreach (Edge *edge, edgeList)
    delete edge;
}

void Node::addEdge(Edge *edge) {
  edgeList << edge;
  edge->adjust();
}

QList<Edge *> Node::edges() const { return edgeList; }

QRectF Node::boundingRect() const {
  return QRectF(-Radius - _pen.width() / 2, -Radius - _pen.width() / 2,
                2 * Radius + _pen.width(), 2 * Radius + _pen.width());
}

QPainterPath Node::shape() const {
  QPainterPath path;
  path.addEllipse(-Radius - _pen.width() / 2, -Radius - _pen.width() / 2,
                  2 * Radius + _pen.width(), 2 * Radius + _pen.width());
  return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *) {
  painter->setBrush(
      (option->state & QStyle::State_Selected ? Qt::cyan : Qt::white));
  painter->setPen(_pen);
  painter->drawEllipse(-Radius, -Radius, 2 * Radius, 2 * Radius);
  painter->drawText(-Radius / 5, 0, QString("%1").arg(id));
  painter->drawText(-Radius / 5, 0 + 10, QString("%1").arg(id));
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value) {
  switch (change) {
  case ItemPositionHasChanged:
    foreach (Edge *edge, edgeList)
      edge->adjust();
    break;
  default:
    break;
  };

  return QGraphicsItem::itemChange(change, value);
}

uint Node::idStatic() { return _idStatic; }

void Node::removeEdge(Edge *edge) {
  QMutableListIterator<Edge *> iter(edgeList);
  while (iter.hasNext()) {
    Edge *e = iter.next();
    if (e == edge) {
      iter.remove();
      break;
    }
  }
}

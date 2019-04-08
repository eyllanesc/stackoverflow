#include "edge.h"
#include "node.h"

#include <QPainter>
#include <QStyleOption>
#include <qmath.h>

uint Edge::_idStatic = 0;

Edge::Edge(Node *sourceNode, Node *destNode) : id(_idStatic++), arrowSize(15) {
  setFlag(QGraphicsItem::ItemIsSelectable);
  source = sourceNode;
  dest = destNode;
  source->addEdge(this);
  if (source != dest)
    dest->addEdge(this);
  adjust();
}

Edge::~Edge() {
  source->removeEdge(this);
  if (source != dest)
    dest->removeEdge(this);
}

Node *Edge::sourceNode() const { return source; }

Node *Edge::destNode() const { return dest; }

void Edge::adjust() {
  if (!source || !dest)
    return;

  if (source != dest) {
    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();
    if (length > qreal(2 * Node::Radius)) {
      QPointF edgeOffset((line.dx() * Node::Radius) / length,
                         (line.dy() * Node::Radius) / length);
      sourcePoint = line.p1() + edgeOffset;
      destPoint = line.p2() - edgeOffset;
    } else {
      sourcePoint = destPoint = line.p1();
    }
  } else {
    sourcePoint = mapFromItem(source, 0, Node::Radius);
    destPoint = mapFromItem(source, Node::Radius, 0);
    prepareGeometryChange();
  }
}

QPainterPath Edge::shape() const {
  m_path;
  if (source != dest) {
    QLineF line =
        QLineF(sourcePoint.x(), sourcePoint.y(), destPoint.x(), destPoint.y());
    qreal radAngle = line.angle() * M_PI / 180;
    qreal selectionOffset = 3;
    qreal dx = selectionOffset * sin(radAngle);
    qreal dy = selectionOffset * cos(radAngle);
    QPointF offset1 = QPointF(dx, dy);
    QPointF offset2 = QPointF(-dx, -dy);
    m_path.moveTo(line.p1() + offset1);
    m_path.lineTo(line.p1() + offset2);
    m_path.lineTo(line.p2() + offset2);
    m_path.lineTo(line.p2() + offset1);
  } else {
    QRectF r = mapRectFromItem(source, source->boundingRect());
    r.moveCenter(r.topRight());
    m_path.addRect(r);
  }
  return m_path;
}

QRectF Edge::boundingRect() const {
  if (!source || !dest)
    return QRectF();

  return m_path.boundingRect();
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *) {
  if (!source || !dest)
    return;

  double angle;
  QPointF peak, destArrowP1, destArrowP2;
  painter->setPen(
      QPen((option->state & QStyle::State_Selected ? Qt::cyan : Qt::black), 2,
           Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  if (source != dest) {
    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
      return;

    // Draw the line itself
    painter->drawLine(line);

    // Draw the arrows
    angle = std::atan2(-line.dy(), line.dx());
    peak = line.p2();
    destArrowP1 =
        destPoint +
        QPointF(sin(angle - M_PI / 1.8) * qMin(arrowSize, line.length()),
                cos(angle - M_PI / 1.8) * qMin(arrowSize, line.length()));
    destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 1.8) *
                                          qMin(arrowSize, line.length()),
                                      cos(angle - M_PI + M_PI / 1.8) *
                                          qMin(arrowSize, line.length()));

  } else {
    painter->drawArc(boundingRect().toRect(), 16 * -90, 16 * 270);
    angle = 1.06 * M_PI;
    destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 1.8) * arrowSize,
                                      cos(angle - M_PI / 1.8) * arrowSize);
    destArrowP2 =
        destPoint + QPointF(sin(angle - M_PI + M_PI / 1.8) * arrowSize,
                            cos(angle - M_PI + M_PI / 1.8) * arrowSize);
    painter->setBrush(
        (option->state & QStyle::State_Selected ? Qt::cyan : Qt::black));
    peak = QPointF(boundingRect().center().x(), boundingRect().bottom());
  }

  painter->setBrush(
      (option->state & QStyle::State_Selected ? Qt::cyan : Qt::black));
  painter->drawPolygon(QPolygonF() << peak << destArrowP1 << destArrowP2);
}

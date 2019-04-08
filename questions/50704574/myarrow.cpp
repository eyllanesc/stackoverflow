#include "myarrow.h"
#include "customrect.h"

#include <QPainter>

#include <cmath>

MyArrow::MyArrow(CustomRect *rect) {
  myrect = rect;
  QPointF p = rect->boundingRect().center();
  updatePosition(p - QPointF(0, 50), p - QPointF(0, 250));
  setFlag(QGraphicsLineItem::ItemIsSelectable);
}

void MyArrow::updatePosition(QPointF p1, QPointF p2) {

  const qreal arrowSize = 20;

  QPainterPath path;

  path.moveTo(p1);
  path.lineTo(p2);

  QPointF diff = p2 - p1;
  double angle = std::atan2(-diff.y(), diff.x());

  QPointF arrowP1 = p1 + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                 cos(angle + M_PI / 3) * arrowSize);
  QPointF arrowP2 = p1 + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                 cos(angle + M_PI - M_PI / 3) * arrowSize);
  QPolygonF arrowHead;
  arrowHead << p1 << arrowP1 << arrowP2 << p1;
  path.moveTo(p1);
  path.addPolygon(arrowHead);

  setPath(path);
}

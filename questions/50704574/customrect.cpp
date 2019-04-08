#include "customrect.h"
#include "myarrow.h"

CustomRect::CustomRect(const QRectF &rect) : QGraphicsRectItem(rect) {
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

void CustomRect::addLine(MyArrow *line) { arrows << line; }

QVariant CustomRect::itemChange(GraphicsItemChange change,
                                const QVariant &value) {
  if (change == ItemPositionChange && scene()) {
    QPointF newPos = value.toPointF();
    moveLineToCenter(newPos);
  }
  return QGraphicsItem::itemChange(change, value);
}

void CustomRect::moveLineToCenter(QPointF newPos) {

  for (MyArrow *arrow : arrows) {
    arrow->setPos(newPos);
  }
}

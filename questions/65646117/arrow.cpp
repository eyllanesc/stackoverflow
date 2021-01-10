#include "arrow.h"
#include "component.h"

#include <QPen>

Arrow::Arrow(Component *startItem, Component *endItem, QGraphicsItem *parent):
    QGraphicsPathItem(parent), mStartItem(startItem), mEndItem(endItem)
{
    mStartItem->addArrow(this);
    mEndItem->addArrow(this);
    setPen(QPen(QColor("red"), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    adjust();
}

void Arrow::adjust()
{
    prepareGeometryChange();
    QPainterPath path;
    path.moveTo(mStartItem->pos());
    path.lineTo(mEndItem->pos());
    setPath(path);
}

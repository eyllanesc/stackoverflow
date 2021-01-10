#include "arrow.h"
#include "component.h"

Component::Component(QGraphicsItem *parent):
    QGraphicsRectItem(parent)
{
    setRect(-40, -40, 80, 80);
    setFlags(QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

void Component::addArrow(Arrow *arrow)
{
    mArrows << arrow;
}

QVariant Component::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemPositionHasChanged){
        for(Arrow * arrow: qAsConst(mArrows)){
            arrow->adjust();
        }
    }
    return QGraphicsRectItem::itemChange(change, value);
}

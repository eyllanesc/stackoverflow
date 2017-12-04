#ifndef DGRAPHICSITEM_H
#define DGRAPHICSITEM_H

#include <QGraphicsRectItem>
#include <QPainter>


class DGraphicsEllipseItem : public QGraphicsEllipseItem
{
public:
    DGraphicsEllipseItem(const QRectF &rect, qreal radius, QGraphicsItem *parent = nullptr):
        QGraphicsEllipseItem(rect, parent){
        mRadius = radius;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
        QGraphicsEllipseItem::paint(painter, option, widget);
        painter->setBrush(brush());
        QRectF r = rect();
        r.setSize(r.size()-mRadius*QSizeF(1, 1));
        r.translate(mRadius*QPointF(1, 1)/2);
        painter->drawEllipse(r);
    }
private:
    qreal mRadius;
};

class DGraphicsRectItem : public QGraphicsRectItem
{
public:
    DGraphicsRectItem(const QRectF &rect, qreal radius, QGraphicsItem *parent = nullptr):
        QGraphicsRectItem(rect, parent){
        mRadius = radius;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
        QGraphicsRectItem::paint(painter, option, widget);
        painter->setBrush(brush());
        QRectF r = rect();
        r.setSize(r.size()-mRadius*QSizeF(1, 1));
        r.translate(mRadius*QPointF(1, 1)/2);
        painter->drawRect(r);
    }
private:
    qreal mRadius;
};
#endif // DGRAPHICSITEM_H

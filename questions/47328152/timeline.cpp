#include "timeline.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QTimer>

#include <QDebug>

TimeLine::TimeLine(Timers *t, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    timer = t;
    timeLineWidth=200000;
    setRect(QRectF(0,0,timeLineWidth,18));
    timeLineScale = 0.1;

}

void TimeLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QRectF rect = boundingRect().toRect();

    QPen pen(Qt::NoPen);
    painter->setPen(pen);
    painter->setBrush(QColor(200,200,200));
    painter->drawRect(rect);

    painter->setPen(Qt::red);
    for(int i=0;i<200;i++)
    {
        painter->drawText(i*30,9,QString::number(i+1));
    }
}


void TimeLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        timer->start();
}

#ifndef TIMELINE_H
#define TIMELINE_H

#include "timers.h"
#include <QGraphicsRectItem>

class TimeLine : public QGraphicsRectItem
{
public:
    TimeLine(Timers *t, QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    int timeLineWidth;
    float timeLineScale;
    Timers *timer;
};

#endif // TIMELINE_H

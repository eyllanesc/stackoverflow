#ifndef RUBBERBANDITEM_H
#define RUBBERBANDITEM_H

#include <QGraphicsLineItem>

class RubberBandItem : public QGraphicsLineItem
{
public:
    RubberBandItem(QGraphicsItem *parent=0);


    QPointF p1() const;
    void setP1(const QPointF &p1);

    QPointF p2() const;
    void setP2(const QPointF &p2);

private:

    QPointF mP1;
    QPointF mP2;

};

#endif // RUBBERBANDITEM_H

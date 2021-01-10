#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsPathItem>

class Component;

class Arrow : public QGraphicsPathItem
{
public:
    Arrow(Component *startItem, Component *endItem, QGraphicsItem *parent = nullptr);
    void adjust();
private:
    Component *mStartItem;
    Component *mEndItem;
};

#endif // ARROW_H

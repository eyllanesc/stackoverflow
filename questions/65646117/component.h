#ifndef COMPONENT_H
#define COMPONENT_H

#include <QGraphicsRectItem>

class Arrow;

class Component : public QGraphicsRectItem
{
public:
    Component(QGraphicsItem *parent = nullptr);
    void addArrow(Arrow *arrow);
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    QVector<Arrow *> mArrows;
};

#endif // COMPONENT_H

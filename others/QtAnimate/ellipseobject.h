#ifndef ELLIPSEOBJECT_H
#define ELLIPSEOBJECT_H

#include <QGraphicsObject>

class EllipseObject : public QGraphicsObject {
  Q_OBJECT
public:
  EllipseObject(QGraphicsItem *parent = 0);

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = 0);
  QRectF boundingRect() const;
};

#endif // ELLIPSEOBJECT_H

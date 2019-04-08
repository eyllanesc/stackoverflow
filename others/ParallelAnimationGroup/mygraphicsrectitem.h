#ifndef MYGRAPHICSRECTITEM_H
#define MYGRAPHICSRECTITEM_H

#include <QGraphicsRectItem>
#include <QObject>

class MyGraphicsRectItem : public QObject, public QGraphicsRectItem {
  Q_OBJECT
  Q_PROPERTY(QPointF position READ position WRITE setPosition)
  Q_PROPERTY(QRectF geometry READ geometry WRITE setGeometry)
public:
  MyGraphicsRectItem(qreal x, qreal y, qreal width, qreal height,
                     QGraphicsItem *parent = 0);
  MyGraphicsRectItem(QObject *parent = 0);
  QPointF position() const;
  void setPosition(const QPointF &position);

  QRectF geometry() const;
  void setGeometry(const QRectF &geometry);
};

#endif // MYGRAPHICSRECTITEM_H

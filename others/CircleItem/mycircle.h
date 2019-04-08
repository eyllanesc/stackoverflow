#ifndef MYCIRCLE_H
#define MYCIRCLE_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class MyCircle : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_PROPERTY(QRect geometry READ geometry WRITE setGeometry)
  Q_INTERFACES(QGraphicsItem)
public:
  explicit MyCircle(QObject *parent = nullptr);

  QRect geometry() const;
  void setGeometry(const QRect &value);

  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);

private:
  QRect rect;
};

#endif // MYCIRCLE_H

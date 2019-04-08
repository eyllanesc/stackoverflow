#ifndef GRAPHICSPIXMAPITEM_H
#define GRAPHICSPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>

class GraphicsPixmapItem : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
public:
  explicit GraphicsPixmapItem(QObject *parent = 0);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
  void newPixmap(const QPixmap p);
};

#endif // GRAPHICSPIXMAPITEM_H

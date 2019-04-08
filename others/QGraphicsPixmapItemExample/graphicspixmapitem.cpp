#include "graphicspixmapitem.h"

#include <QGraphicsSceneMouseEvent>

GraphicsPixmapItem::GraphicsPixmapItem(QObject *parent) : QObject(parent) {}

void GraphicsPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  QPoint p = QPoint(event->pos().x(), event->pos().y());
  QPixmap pix = pixmap();
  if (!pix.isNull()) {
    QRect rect(QPoint(), pix.rect().size() / 2);
    rect.moveCenter(p);
    QPixmap modified = pix.copy(rect);
    modified =
        modified.scaled(pix.rect().size(), Qt::KeepAspectRatioByExpanding);
    emit newPixmap(modified);
  }
  QGraphicsPixmapItem::mousePressEvent(event);
}

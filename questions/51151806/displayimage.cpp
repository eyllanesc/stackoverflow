#include "displayimage.h"

#include <QEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>

DisplayImage::DisplayImage(QWidget *parent) : QGraphicsView(parent) {
  scene = new QGraphicsScene(this);
  pixmapItem = new QGraphicsPixmapItem(pixmap);
  scene->addItem(pixmapItem);
  setScene(scene);
  scene->installEventFilter(this);
}

void DisplayImage::displayImg(const QImage &image) {
  pixmap = QPixmap::fromImage(image);
  pixmapItem->setPixmap(pixmap);
  setSceneRect(image.rect());
  fitInView(pixmapItem, Qt::KeepAspectRatio);
  centerOn(pixmapItem);
}

bool DisplayImage::eventFilter(QObject *watched, QEvent *event) {
  if (watched == scene) {
    // press event
    QGraphicsSceneMouseEvent *mouseSceneEvent;
    if (event->type() == QEvent::GraphicsSceneMousePress) {
      mouseSceneEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
      qDebug() << mouseSceneEvent->scenePos()
               << mouseSceneEvent->lastScenePos();
    }
    // move event
    else if (event->type() == QEvent::GraphicsSceneMouseMove) {
      mouseSceneEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
      qDebug() << mouseSceneEvent->scenePos()
               << mouseSceneEvent->lastScenePos();
    }
    // release event
    else if (event->type() == QEvent::GraphicsSceneMouseRelease) {
      mouseSceneEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
      qDebug() << mouseSceneEvent->scenePos()
               << mouseSceneEvent->lastScenePos();
    }
  }
  return QGraphicsView::eventFilter(watched, event);
}

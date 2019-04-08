#include "scene.h"
#include "block.h"

#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>

Scene::Scene(QObject *parent) : QGraphicsScene(parent) {
  setBackgroundBrush(Qt::lightGray);
}

void Scene::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
  if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
    event->setAccepted(true);
}

void Scene::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
  if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
    event->setAccepted(true);
}

void Scene::dropEvent(QGraphicsSceneDragDropEvent *event) {

  QByteArray encoded =
      event->mimeData()->data("application/x-qabstractitemmodeldatalist");
  QDataStream stream(&encoded, QIODevice::ReadOnly);

  QStringList colors;

  while (!stream.atEnd()) {
    int row, col;
    QMap<int, QVariant> roleDataMap;
    stream >> row >> col >> roleDataMap;
    colors << roleDataMap[Qt::DisplayRole].toString();
  }
  QPointF posView = event->scenePos();
  for (const QString &color : colors) {
    Block *newBlock = new Block(color);
    newBlock->setPos(posView);
    addItem(newBlock);
  }
}

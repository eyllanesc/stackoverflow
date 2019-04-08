#include "graphicsscene.h"

#include <QGraphicsSceneMouseEvent>

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent) {
  setBackgroundBrush(Qt::gray);
}

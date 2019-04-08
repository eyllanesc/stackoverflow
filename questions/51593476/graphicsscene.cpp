#include "graphicsscene.h"

GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(parent), mRef(nullptr) {
  connect(this, &GraphicsScene::selectionChanged, this,
          &GraphicsScene::onSelectionChanged);
}

void GraphicsScene::moveSelecteds(Qt::Alignment aligment) {
  QList<QGraphicsItem *> its = selectedItems();
  if (its.size() < 2)
    return;
  if (!its.removeOne(mRef))
    return;
  move(mRef, its, aligment);
}

void GraphicsScene::onSelectionChanged() {
  if (selectedItems().isEmpty()) {
    mRef = nullptr;
  } else if (selectedItems().size() == 1) {
    mRef = selectedItems().first();
  }
}

void GraphicsScene::move(QGraphicsItem *ref, QList<QGraphicsItem *> others,
                         Qt::Alignment aligment) {
  QPointF p;
  switch (aligment) {
  case Qt::AlignLeft:
    p = QPointF(ref->mapToScene(ref->boundingRect().topLeft()).x(), 0);
    break;
  case Qt::AlignRight:
    p = QPointF(ref->mapToScene(ref->boundingRect().topRight()).x(), 0);
    break;
  case Qt::AlignTop:
    p = QPointF(0, ref->mapToScene(ref->boundingRect().topLeft()).y());
    break;
  case Qt::AlignBottom:
    p = QPointF(0, ref->mapToScene(ref->boundingRect().bottomLeft()).y());
    break;
  }

  for (QGraphicsItem *o : others) {
    QPointF delta;
    switch (aligment) {
    case Qt::AlignLeft: {
      delta = p - QPointF(o->mapToScene(o->boundingRect().topLeft()).x(), 0);
      break;
    }
    case Qt::AlignRight: {
      delta = p - QPointF(o->mapToScene(o->boundingRect().topRight()).x(), 0);
      break;
    }
    case Qt::AlignTop: {
      delta = p - QPointF(0, o->mapToScene(o->boundingRect().topLeft()).y());
      break;
    }
    case Qt::AlignBottom: {
      delta = p - QPointF(0, o->mapToScene(o->boundingRect().bottomLeft()).y());
      break;
    }
    }
    o->moveBy(delta.x(), delta.y());
  }
}

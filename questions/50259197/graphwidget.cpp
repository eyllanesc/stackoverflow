#include "graphwidget.h"

GraphWidget::GraphWidget(QWidget *parent) : QGraphicsView(parent) {
  QGraphicsScene *scene = new QGraphicsScene(this);
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->setSceneRect(-200, -200, 500, 500);
  setScene(scene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  scale(qreal(0.8), qreal(0.8));
}

void GraphWidget::addNode() {
  static int x = 0, y = -100;
  Node *node1 = new Node(this);
  scene()->addItem(node1);
  switch ((Node::idStatic() - 1) % 2) {
  case 0:
    x -= 2 * Node::Radius + 10;
    y += 2 * Node::Radius + 10;
    break;
  case 1:
    x += 2 * Node::Radius + 10;
    break;
  }
  node1->setPos(x, y);
}

void GraphWidget::keyPressEvent(QKeyEvent *event) {
  Node *selectedNode = nullptr;
  try {
    selectedNode = qgraphicsitem_cast<Node *>(scene()->selectedItems().at(0));
  } catch (...) {
    selectedNode = nullptr;
  }

  switch (event->key()) {
  case Qt::Key_Up:
    if (selectedNode)
      selectedNode->moveBy(0, -20);
    break;
  case Qt::Key_Down:
    if (selectedNode)
      selectedNode->moveBy(0, 20);
    break;
  case Qt::Key_Left:
    if (selectedNode)
      selectedNode->moveBy(-20, 0);
    break;
  case Qt::Key_Right:
    if (selectedNode)
      selectedNode->moveBy(20, 0);
    break;
  case Qt::Key_Plus:
    zoomIn();
    break;
  case Qt::Key_Minus:
    zoomOut();
    break;
  case Qt::Key_Space:
  case Qt::Key_Enter:
    shuffle();
    break;
  default:
    QGraphicsView::keyPressEvent(event);
  }
}

#if QT_CONFIG(wheelevent)
void GraphWidget::wheelEvent(QWheelEvent *event) {
  scaleView(pow((double)2, -event->delta() / 240.0));
}
#endif

void GraphWidget::scaleView(qreal scaleFactor) {
  qreal factor = transform()
                     .scale(scaleFactor, scaleFactor)
                     .mapRect(QRectF(0, 0, 1, 1))
                     .width();
  if (factor < 0.07 || factor > 100)
    return;

  scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle() {
  foreach (QGraphicsItem *item, scene()->items()) {
    if (qgraphicsitem_cast<Node *>(item))
      item->setPos(-150 + QRandomGenerator::global()->bounded(300),
                   -150 + QRandomGenerator::global()->bounded(300));
  }
}

void GraphWidget::zoomIn() { scaleView(qreal(1.2)); }

void GraphWidget::zoomOut() { scaleView(1 / qreal(1.2)); }

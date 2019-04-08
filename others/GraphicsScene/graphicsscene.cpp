#include "graphicsscene.h"
#include "mainwindow.h"
#include <QDebug>

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent) {
  mRubberband = new RubberBandItem;
  setBackgroundBrush(Qt::black);
  myNumber = 0;
  CoordinateNumber = 0;

  // connect(this, &GraphicsScene::sceneRectChanged, rubberband,
  // &RubberBandItem::onRectChanged);
}

void GraphicsScene::mouseDoubleClickEvent(
    QGraphicsSceneMouseEvent *mouseEvent) {
  //    mousePoint = mouseEvent->scenePos();
  //    MouseX = mousePoint.x();
  //    MouseY = mousePoint.y();
  qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
  QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  mousePoint = mouseEvent->scenePos();
  MouseX = mouseEvent->scenePos().x();
  MouseY = mouseEvent->scenePos().y();

  emit changedMousePosition(mousePoint);

  // if (CoordinateNumber == 1) {
  mRubberband->setP2(mouseEvent->scenePos());
  // qDebug()<<mRubberband->p2();
  //}

  QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  mousePoint = mouseEvent->scenePos();
  MouseX = mouseEvent->scenePos().x();
  MouseY = mouseEvent->scenePos().y();
  mousePoints.append(mouseEvent->scenePos());

  CoordinateNumber++;
  // if (CoordinateNumber == 1) {

  bool isItem = false;
  for (auto item : items()) {
    if (item == mRubberband) {
      isItem = true;
      break;
    }
  }
  if (isItem)
    removeItem(mRubberband);
  else
    addItem(mRubberband);
  mRubberband->setP1(mouseEvent->scenePos());
  //}

  MainWindow *mainWindow = new MainWindow();
  mainWindow->Count++;

  if (mousePoints.size() == 2) {
    myNumber++;

    emit changedNumber(myNumber);

    QColor color;
    color.setRgb(128, 0, 255);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(20);
    pen.setCapStyle(Qt::RoundCap);
    // addLine(mousePoints.at(0).x(), mousePoints.at(0).y(),
    // mousePoints.at(1).x(), mousePoints.at(1).y(), pen);

    mousePoints.clear();
    CoordinateNumber = 0;
    // RubberBand.Drawn = false;
  }

  QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  mousePoint = mouseEvent->scenePos();
  MouseX = mouseEvent->scenePos().x();
  MouseY = mouseEvent->scenePos().y();
  QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

QPointF GraphicsScene::getMousePoint(void) { return mousePoint; }

int GraphicsScene::getMouseX(void) {
  MouseX = mousePoint.x();
  return mousePoint.x();
}

int GraphicsScene::getMouseY(void) {
  MouseY = mousePoint.y();
  return mousePoint.y();
}

void GraphicsScene::setNumber(int num) { myNumber = num; }

int GraphicsScene::getNumber(void) { return myNumber; }

void GraphicsScene::myLine(int x1, int y1, int x2, int y2) {
  //    drawLine(x1, y1, x2, y2);
  QPoint point1, point2;
  point1.setX(x1);
  point1.setY(y1);
  point2.setX(x2);
  point2.setY(y2);
}

void GraphicsScene::drawLine(int x1, int y1, int x2, int y2) {
  // Just draw something by clicking a button

  qDebug() << "line2"; // This debug message is shown

  QColor color;
  color.setRgb(128, 0, 255);
  QPen pen;
  pen.setColor(color);
  pen.setWidth(20);
  pen.setCapStyle(Qt::RoundCap);

  // addLine(x1, y1, x2, y2, pen); // Didn't draw the line on the scene
}

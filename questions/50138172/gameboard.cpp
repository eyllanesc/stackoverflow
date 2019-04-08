#include "gameboard.hh"
#include "bubbleitem.hh"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

GameBoard::GameBoard(QObject *parent) : QGraphicsScene{parent} {
  setSceneRect(0, 0, WIDTH * GRID_SIDE, HEIGHT * GRID_SIDE);
}

void GameBoard::drawBackground(QPainter *painter, QRectF const &) {
  QColor backGroundColor(225, 225, 225);

  painter->save();
  painter->setPen(QPen(Qt::darkGray, 1));
  painter->setBrush(QBrush());
  painter->drawRect(sceneRect().toRect());
  painter->restore();

  // Draw gridlines for the game area.
  // REMOVE THE COMMENT IF YOU WANT TO USE THE GRID FOR DEBUGGING!

  for (int row = 0; row < HEIGHT; row++) {
    for (int column = 0; column < WIDTH; column++) {
      QRectF square(column * GRID_SIDE, row * GRID_SIDE, GRID_SIDE, GRID_SIDE);
      painter->fillRect(square, backGroundColor);
      painter->drawRect(square);
    }
  }
}

void GameBoard::addBubble(int column, int row, std::shared_ptr<Bubble> bubble) {
  // Create a new graphical item and add it to the scene so it will be drawn.
  BubbleItem *item = new BubbleItem(bubble, bubble->getColor(), 0);
  addItem(item);

  // Set the correct position within the scene.
  QPointF position = gridToPoint(column, row);
  item->setPos(position);
}

QPoint GameBoard::gridToPoint(int column, int row) const {
  return QPoint(GRID_SIDE * column, GRID_SIDE * row);
}

void GameBoard::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsScene::mousePressEvent(event);
  if (sceneRect().contains(event->scenePos()))
    Q_EMIT mouseClick(event->scenePos());
}

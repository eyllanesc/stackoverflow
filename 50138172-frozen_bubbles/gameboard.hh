#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "splashitem.h"

#include <QGraphicsScene>
#include <memory>
#include <bubble.hh>

const static int HEIGHT = 12;
const static int WIDTH = 10;

// Size of the grid i.e. both width and height.
const static int GRID_SIDE = 50;

class GameBoard : public QGraphicsScene
{
    Q_OBJECT
public:
    GameBoard(QObject *parent=nullptr);
    void addBubble(int column, int row, std::shared_ptr<Bubble> bubble);
    Q_SIGNAL void mouseClick(const QPointF & p);
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    QPoint gridToPoint(int column, int row) const;
};

#endif // GAMEBOARD_H

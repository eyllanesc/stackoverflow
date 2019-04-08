#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsPathItem>

class Block : public QGraphicsPathItem {
public:
  Block(QString color, QGraphicsItem *parent = nullptr);
};

#endif // BLOCK_H

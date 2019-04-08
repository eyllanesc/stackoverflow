#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QPainter>
#include <QPointF>

#include "rubberbanditem.h"

class GraphicsScene : public QGraphicsScene {
  Q_OBJECT
public:
  explicit GraphicsScene(QObject *parent = 0);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

  QPointF getMousePoint(void);
  int getMouseX(void);
  int getMouseY(void);
  int getNumber(void);
  void setNumber(int num);

  void myLine(int x1, int y1, int x2, int y2);

  QPointF mousePoint;
  int MouseX, MouseY;
  int myNumber;

  void drawLine(int x1, int y1, int x2, int y2);

signals:
  void changedMousePosition(QPointF mousePoint);
  void changedNumber(int myNumber);

public slots:

private:
  QList<QPointF> mousePoints;

  int CoordinateNumber;

  //    object Objects[1024];

  int NoOfObjects;
  RubberBandItem *mRubberband;
};

#endif // GRAPHICSSCENE_H

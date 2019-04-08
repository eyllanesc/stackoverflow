#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include "edge.h"
#include "node.h"
#include <QGraphicsView>

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>

class Node;

class GraphWidget : public QGraphicsView {
  Q_OBJECT

public:
  GraphWidget(QWidget *parent = 0);

  void itemMoved();

public slots:
  void addNode();
  void shuffle();
  void zoomIn();
  void zoomOut();

protected:
  void keyPressEvent(QKeyEvent *event) override;
#if QT_CONFIG(wheelevent)
  void wheelEvent(QWheelEvent *event) override;
#endif
  void scaleView(qreal scaleFactor);

private:
};

#endif // GRAPHWIDGET_H

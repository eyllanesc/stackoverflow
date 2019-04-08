#include "graphicsview.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QtMath>

#include "ellipseobject.h"

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) {

  QGraphicsScene *scene = new QGraphicsScene(this);

  scene->setBackgroundBrush(Qt::black);

  group = new QParallelAnimationGroup(this);

  setCacheMode(QGraphicsView::CacheBackground);

  int p = 180;
  QPointF center(scene->sceneRect().center());

  qreal r = 100.0;
  qreal delta = 10.0;

  int number_of_items = 10;

  QPainterPath path;

  path.addEllipse(center, r + delta, r + delta);
  path.addEllipse(center, r - delta, r - delta);

  scene->addPath(path, QPen(Qt::white), QBrush(Qt::green));

  for (int i = 0; i < number_of_items; i++) {
    EllipseObject *item = new EllipseObject;
    QPropertyAnimation *animation = new QPropertyAnimation(item, "pos");
    for (int j = 0; j < p; j++) {
      animation->setKeyValueAt(
          1.0 * j / (p - 1), (r + delta * sin(2 * M_PI * j / p)) *
                                 QPointF(qSin(2 * M_PI * i / number_of_items),
                                         qCos(2 * M_PI * i / number_of_items)));
    }
    animation->setDuration(2000);
    group->addAnimation(animation);
    scene->addItem(item);
  }
  group->start();
  connect(group, &QParallelAnimationGroup::finished, [=]() { group->start(); });

  setScene(scene);
}

void GraphicsView::closeEvent(QCloseEvent *event) {
  Q_UNUSED(event)
  group->stop();
}

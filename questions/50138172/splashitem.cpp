#include "splashitem.h"
#include "gameboard.hh"

SplashItem::SplashItem(QObject *parent) : QObject(parent) {
  const int SPLASH_SIZE = 50;

  QPixmap pixmap("://images/bluesplash.png");
  setPixmap(pixmap.scaledToHeight(SPLASH_SIZE));

  // Offset the image evenly around its centerpoint.
  setOffset(-SPLASH_SIZE / 2, -SPLASH_SIZE / 2);

  // Rotate the image according to the travel direction.
  // The original image travels from left to right.
  setRotation(270);
  hide();
  setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
  m_animation = new QPropertyAnimation(this, "pos");
  m_animation->setDuration(2000);
  connect(m_animation, &QPropertyAnimation::finished, this,
          &SplashItem::onFinished);
  connect(m_animation, &QPropertyAnimation::valueChanged, this,
          &SplashItem::verifyCollide);
}

void SplashItem::setStartValue(const QPointF &p) {
  m_animation->setStartValue(p);
}

void SplashItem::setEndValue(const QPointF &p) {
  if (m_animation->state() == QPropertyAnimation::Running)
    return;
  m_animation->setEndValue(p);
  show();
  m_animation->start();
}

void SplashItem::onFinished() { hide(); }
void SplashItem::verifyCollide() {
  for (QGraphicsItem *it : collidingItems()) {
    scene()->removeItem(it);
    delete it;
  }
}

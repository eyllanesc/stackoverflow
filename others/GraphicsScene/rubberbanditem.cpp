#include "rubberbanditem.h"

#include <QDebug>
#include <QPainter>

RubberBandItem::RubberBandItem(QGraphicsItem *parent)
    : QGraphicsLineItem(parent) {
  setPen(QPen(Qt::white));
}

QPointF RubberBandItem::p1() const { return mP1; }

void RubberBandItem::setP1(const QPointF &p1) {
  mP1 = p1;
  setLine(mP1.x(), mP1.y(), mP2.x(), mP2.y());
}

QPointF RubberBandItem::p2() const { return mP2; }

void RubberBandItem::setP2(const QPointF &p2) {
  mP2 = p2;
  setLine(mP1.x(), mP1.y(), mP2.x(), mP2.y());
}

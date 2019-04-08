#include "csprite2d.h"

CSprite2D::CSprite2D(QObject *parent) : QObject(parent) {
  mPos = QPoint(10, 10);
}

CSprite2D::~CSprite2D() {}

QString CSprite2D::name() const { return mName; }

void CSprite2D::setName(const QString &name) { mName = name; }

QPoint CSprite2D::pos() const { return mPos; }

void CSprite2D::setPos(const QPoint &pos) {
  mPos = pos;
  emit onChanged();
}

QColor CSprite2D::color() const { return mColor; }

void CSprite2D::setColor(const QColor &color) { mColor = color; }

void CSprite2D::paint(QPainter *painter, QPaintEvent *event) {
  Q_UNUSED(event)
  QPen pen(Qt::white);
  painter->setPen(pen);
  QBrush brush(mColor);
  painter->setBrush(brush);
  painter->drawEllipse(mPos, 30, 30);
  painter->drawText(mPos, mName);
}

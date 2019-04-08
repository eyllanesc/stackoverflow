#include "lineitem.h"

#include <QPainter>

void LineItem::paint(QPainter *painter) {
  painter->setRenderHint(QPainter::Antialiasing, true);
  QPen pen(m_lineColor, 2);
  painter->setPen(pen);
  painter->drawLine(m_startPos, m_endPos);
}

QPoint LineItem::startPos() const { return m_startPos; }

void LineItem::setStartPos(const QPoint &startPos) {
  if (m_startPos == startPos)
    return;
  m_startPos = startPos;
  emit startPosChanged();
  update();
}

QPoint LineItem::endPos() const { return m_endPos; }

void LineItem::setEndPos(const QPoint &endPos) {
  if (m_endPos == endPos)
    return;
  m_endPos = endPos;
  emit endPosChanged();
  update();
}

QColor LineItem::lineColor() const { return m_lineColor; }

void LineItem::setLineColor(const QColor &lineColor) {
  if (m_lineColor == lineColor)
    return;
  m_lineColor = lineColor;
  emit lineColorChanged();
  update();
}

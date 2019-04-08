#include "graphicsview.h"

#include <QWheelEvent>
#include <QtMath>

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) {}

void GraphicsView::setModifiers(const Qt::KeyboardModifiers &modifiers) {
  m_modifiers = modifiers;
}

void GraphicsView::wheelEvent(QWheelEvent *event) {
  if (event->modifiers() == m_modifiers) {
    double angle = event->orientation() == Qt::Vertical
                       ? event->angleDelta().y()
                       : event->angleDelta().x();
    double factor = qPow(base, angle);
    applyZoom(factor, event->pos());
  }
}

void GraphicsView::applyZoom(double factor, const QPoint &fixedViewPos) {
  QPointF fixedScenePos = mapToScene(fixedViewPos);
  centerOn(fixedScenePos);
  scale(factor, factor);
  QPointF delta =
      mapToScene(fixedViewPos) - mapToScene(viewport()->rect().center());
  centerOn(fixedScenePos - delta);
}

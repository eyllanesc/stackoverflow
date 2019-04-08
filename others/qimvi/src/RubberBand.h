#pragma once

#include "customrubberband.h"
#include <QGraphicsItem>
#include <functional>

class RubberBand : public QObject {
  Q_OBJECT

public:
  RubberBand(QObject *parent = nullptr);
  ~RubberBand();
  void SetPixmapItem(QGraphicsPixmapItem *pixmapItem);
  std::function<void(QPoint)> MousePositionTracker;
  std::function<void(QRect)> SelectionTracker;
  std::function<void(int, QPoint)> WheelTracker;
  bool IsSelectionActive() const;
  QRect GetSelection() const;

private:
  bool eventFilter(QObject *watched, QEvent *event) override;
  void mouseWheelEvent(QWheelEvent *event) const;
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  CustomRubberBand rubberBand;
  QPoint origin;
  QGraphicsPixmapItem *pixmapItem;
  static QPointF ClipCoordinatesInRect(QPointF point, QRectF clippingBounds);
  static QPoint CoordinatesItemToGlobal(QGraphicsItem *item, QPointF point);
  static QPointF CoordinatesGlobalToItem(QGraphicsItem *item, QPoint point);
  QPoint RelativeClippedCoordinates(QPoint globalPos) const;
  QRectF selectionRect;
};

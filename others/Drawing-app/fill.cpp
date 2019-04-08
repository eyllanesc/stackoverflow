#include "drawarea.h"
#include "shape.h"

#include <QPoint>

#include <vector>

namespace DrawApp {
class Fill : public Shape {
public:
  explicit Fill(DrawArea *, const QPoint &, int, const QColor &,
                const QColor &);

protected:
  virtual void doDraw(QPainter &painter) override;
  virtual QRect doRect() const override;
  virtual void doUpdate(const QPoint &toPoint) override;

private:
  std::vector<QPoint> pointsSet;
  QRect _r;
};

Fill::Fill(DrawArea *drawArea, const QPoint &topLeft, int strokeWidth,
           const QColor &fillColor, const QColor &)
    : Shape(strokeWidth, fillColor),
      pointsSet(drawArea->floodFill(topLeft, fillColor.rgb())),
      _r(topLeft, topLeft) {
  for (const QPoint &p : pointsSet) {
    if (p.x() < _r.left()) {
      _r.setLeft(p.x());
    } else if (p.x() > _r.right()) {
      _r.setRight(p.x());
    }

    if (p.y() < _r.top()) {
      _r.setTop(p.y());
    } else if (p.y() > _r.bottom()) {
      _r.setBottom(p.y());
    }
  }
}

void Fill::doDraw(QPainter &painter) {
  painter.drawPoints(pointsSet.data(), static_cast<int>(pointsSet.size()));
}

QRect Fill::doRect() const { return _r; }

void Fill::doUpdate(const QPoint &) {
  // Fill once created. Nothing should be done when moving.
}

std::unique_ptr<Shape> createFill(DrawArea *drawArea, const QPoint &topLeft,
                                  int penWidth, const QColor &fillColor,
                                  const QColor &) {
  return std::unique_ptr<Shape>(
      new Fill(drawArea, topLeft, penWidth, fillColor, QColor()));
}
} // namespace DrawApp

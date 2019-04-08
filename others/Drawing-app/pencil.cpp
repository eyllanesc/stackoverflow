#include "shape.h"

#include <QPolygon>

namespace DrawApp {

class Pencil : public Shape {
public:
  explicit Pencil(const QPoint &, int, const QColor &, const QColor &);

protected:
  virtual void doDraw(QPainter &) override;
  virtual QRect doRect() const override;
  virtual void doUpdate(const QPoint &) override;

private:
  QPolygon _pointsSet;
};

Pencil::Pencil(const QPoint &topLeft, int strokeWidth,
               const QColor &strokeColor, const QColor &fillColor)
    : Shape(strokeWidth, strokeColor) {
  update(topLeft);
}

void Pencil::doDraw(QPainter &painter) { painter.drawPolyline(_pointsSet); }

QRect Pencil::doRect() const { return _pointsSet.boundingRect(); }

void Pencil::doUpdate(const QPoint &pointToAdd) { _pointsSet << pointToAdd; }

std::unique_ptr<Shape> createPencil(const QPoint &topLeft, int strokeWidth,
                                    const QColor &strokeColor,
                                    const QColor &fillColor) {
  return std::unique_ptr<Shape>(
      new Pencil(topLeft, strokeWidth, strokeColor, fillColor));
}

std::unique_ptr<Shape> createEraser(const QPoint &topLeft, int strokeWidth,
                                    const QColor &, const QColor &) {
  return std::unique_ptr<Shape>(
      new Pencil(topLeft, strokeWidth, Qt::white, Qt::white));
}
} // namespace DrawApp

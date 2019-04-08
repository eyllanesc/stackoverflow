#include "shape.h"

namespace DrawApp {
class Ellipse : public Shape {
public:
  explicit Ellipse(const QPoint &, int, const QColor &, const QColor &);

protected:
  virtual void doDraw(QPainter &) override;
  virtual QRect doRect() const override;
  virtual void doUpdate(const QPoint &) override;

private:
  QRect _ellipse;
};

Ellipse::Ellipse(const QPoint &topLeft, int strokeWidth,
                 const QColor &strokeColor, const QColor &fillColor)
    : Shape(strokeWidth, strokeColor), _ellipse(topLeft, topLeft) {}

void Ellipse::doDraw(QPainter &painter) {
  if (!_ellipse.isNull()) {
    painter.drawEllipse(_ellipse.normalized());
    // painter.fill(_ellipse, QBrush(_fillColor, Qt::SolidPattern));
  }
}
QRect Ellipse::doRect() const { return _ellipse.normalized(); }
void Ellipse::doUpdate(const QPoint &toPoint) {
  _ellipse.setBottomRight(toPoint);
}

std::unique_ptr<Shape> createEllipse(const QPoint &topLeft, int strokeWidth,
                                     const QColor &strokeColor,
                                     const QColor &fillColor) {
  return std::unique_ptr<Shape>(
      new Ellipse(topLeft, strokeWidth, strokeColor, fillColor));
}
} // namespace DrawApp

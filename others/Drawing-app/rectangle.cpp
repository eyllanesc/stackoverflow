#include "shape.h"

namespace DrawApp {
class Rectangle : public Shape {
public:
  explicit Rectangle(const QPoint &, int, const QColor &, const QColor &);

protected:
  virtual void doDraw(QPainter &) override;
  virtual QRect doRect() const override;
  virtual void doUpdate(const QPoint &) override;

private:
  QRect _rectangle;
};

Rectangle::Rectangle(const QPoint &topLeft, int strokeWidth,
                     const QColor &strokeColor, const QColor &fillColor)
    : Shape(strokeWidth, strokeColor, fillColor), _rectangle(topLeft, topLeft) {

}

void Rectangle::doDraw(QPainter &painter) {
  if (!_rectangle.isNull()) {
    painter.drawRect(_rectangle.normalized());
    QRect fillRect(_rectangle.normalized());
    fillRect.setX(fillRect.x() + 1);
    fillRect.setY(fillRect.y() + 1);
    painter.fillRect(fillRect, painter.brush());
  }
}

QRect Rectangle::doRect() const { return _rectangle.normalized(); }

void Rectangle::doUpdate(const QPoint &toPoint) {
  _rectangle.setBottomRight(toPoint);
}

std::unique_ptr<Shape> createRectangle(const QPoint &topLeft, int strokeWidth,
                                       const QColor &strokeColor,
                                       const QColor &fillColor) {
  return std::unique_ptr<Shape>(
      new Rectangle(topLeft, strokeWidth, strokeColor, fillColor));
}
} // namespace DrawApp

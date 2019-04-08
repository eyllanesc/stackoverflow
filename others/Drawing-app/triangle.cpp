#include "shape.h"

namespace DrawApp {
class Triangle : public Shape {
public:
  explicit Triangle(const QPoint &, int, const QColor &, const QColor &);

protected:
  virtual void doDraw(QPainter &) override;
  virtual QRect doRect() const override;
  virtual void doUpdate(const QPoint &) override;

private:
  QRect _triangle;
};

Triangle::Triangle(const QPoint &topLeft, int strokeWidth,
                   const QColor &strokeColor, const QColor &fillColor)
    : Shape(strokeWidth, strokeColor), _triangle(topLeft, topLeft) {}

void Triangle::doDraw(QPainter &painter) {
  if (!_triangle.isNull()) {
    const bool drawLeftLowerCorner(_triangle.width() < 0);
    QRect triangle(_triangle.normalized());
    QVector<QPoint> points;
    points.append(QPoint(triangle.x(), triangle.y()));
    points.append(QPoint(triangle.x() + triangle.width(), triangle.y()));
    if (drawLeftLowerCorner) {
      points.append(QPoint(triangle.x(), triangle.y() + triangle.height()));
    } else {
      points.append(QPoint(triangle.x() + triangle.width(),
                           triangle.y() + triangle.height()));
    }
    painter.drawPolygon(QPolygon(points));
  }
}

QRect Triangle::doRect() const { return _triangle.normalized(); }

void Triangle::doUpdate(const QPoint &toPoint) {
  _triangle.setBottomRight(toPoint);
}

std::unique_ptr<Shape> createTriangle(const QPoint &topLeft, int strokeWidth,
                                      const QColor &strokeColor,
                                      const QColor &fillColor) {
  return std::unique_ptr<Shape>(
      new Triangle(topLeft, strokeWidth, strokeColor, fillColor));
}
} // namespace DrawApp

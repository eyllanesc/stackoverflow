#include "shape.h"

namespace DrawApp {

Shape::Shape(int strokeWidth, const QColor &strokeColor,
             const QColor &fillColor)
    : _strokeWidth(strokeWidth), _strokeColor(strokeColor),
      _fillColor(fillColor) {}
Shape::~Shape() {}

void Shape::draw(QPainter &painter) {
  const QPen prevPen(painter.pen());
  painter.setPen(QPen(_strokeColor, _strokeWidth, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
  painter.setBrush(QBrush(Qt::yellow));
  doDraw(painter);
  painter.setPen(prevPen);
}

QRect Shape::rect() const {
  const int outlineAddition(0.5 * _strokeWidth + 2);
  return doRect().adjusted(-outlineAddition, -outlineAddition, +outlineAddition,
                           +outlineAddition);
}

void Shape::update(const QPoint &toPoint) { doUpdate(toPoint); }

} // namespace DrawApp

#ifndef _TROFIMOV_SHAPE_H_
#define _TROFIMOV_SHAPE_H_

#include <QColor>
#include <QPainter>
#include <QPoint>
#include <QRect>

#include <memory>

namespace DrawApp {

class DrawArea;

class Shape {
public:
  Shape(int, const QColor &, const QColor &defaultFill = QColor());

  virtual ~Shape();
  void draw(QPainter &painter);
  QRect rect() const;
  void update(const QPoint &toPoint);

protected:
  virtual void doDraw(QPainter &painter) = 0;
  virtual QRect doRect() const = 0;
  virtual void doUpdate(const QPoint &toPoint) = 0;
  QColor _fillColor;

private:
  int _strokeWidth;
  QColor _strokeColor;
};

std::unique_ptr<Shape> createPencil(const QPoint &, int, const QColor &,
                                    const QColor &);
std::unique_ptr<Shape> createEraser(const QPoint &, int, const QColor &,
                                    const QColor &);
std::unique_ptr<Shape> createRectangle(const QPoint &, int, const QColor &,
                                       const QColor &);
std::unique_ptr<Shape> createEllipse(const QPoint &, int, const QColor &,
                                     const QColor &);
std::unique_ptr<Shape> createTriangle(const QPoint &, int, const QColor &,
                                      const QColor &);
std::unique_ptr<Shape> createFill(DrawArea *, const QPoint &, int,
                                  const QColor &, const QColor &);
} // namespace DrawApp

#endif

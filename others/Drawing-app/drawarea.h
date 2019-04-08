#ifndef _TROFIMOV_DRAW_AREA_H_
#define _TROFIMOV_DRAW_AREA_H_

#include "shape.h"

#include <QUndoStack>
#include <QWidget>

#include <functional>
#include <memory>

namespace DrawApp {
class DrawArea : public QWidget {
  Q_OBJECT
public:
  typedef std::function<std::unique_ptr<Shape>(const QPoint &, int,
                                               const QColor &, const QColor &)>
      DrawingFactory;

  explicit DrawArea(QUndoStack *, QWidget *parent = 0);

  bool isModified() const;

  bool createNewDrawing();
  bool openDrawing(const QString &);
  bool saveDrawing(const QString &, const char *);

  void setStrokeColor(const QColor &);
  void setFillColor(const QColor &);
  void setPenWidth(int);

  QColor getPenColor() const { return _strokeColor; }
  int getPenWidth() const { return _strokeWidth; }

  void setDrawingFactory(DrawingFactory);

  void flip(bool, bool);
  void rotate(qreal);

  std::vector<QPoint> floodFill(const QPoint &, const QRgb &);

protected:
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent *);

private:
  QImage _mainDrawing;
  QUndoStack *_undoStack;

  int _strokeWidth;
  QColor _strokeColor;
  QColor _fillColor;

  DrawingFactory _factory;
  std::unique_ptr<Shape> _currentShape;
};

} // namespace DrawApp

#endif

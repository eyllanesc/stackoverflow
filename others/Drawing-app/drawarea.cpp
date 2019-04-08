#include "drawarea.h"

#include "command.h"
#include "floodfill.h"

#include <QCloseEvent>
#include <QEvent>
#include <QPainter>

#include <algorithm>

namespace DrawApp {
DrawArea::DrawArea(QUndoStack *undoStack, QWidget *parent)
    : QWidget(parent), _undoStack(undoStack), _strokeWidth(1),
      _strokeColor(Qt::black), _fillColor(Qt::yellow) {
  // this->setCursor(QCursor(Qt::CustomCursor));
}

bool DrawArea::isModified() const { return !_undoStack->isClean(); }

std::vector<QPoint> DrawArea::floodFill(const QPoint &pos, const QRgb &color) {
  return DrawApp::floodFill(&_mainDrawing, pos, color);
}

void DrawArea::flip(bool horizontally, bool vertically) {
  _undoStack->push(
      new FlipCommand(this, &_mainDrawing, horizontally, vertically));
}

void DrawArea::rotate(qreal deg) {
  _undoStack->push(new RotateCommand(this, &_mainDrawing, deg));
}

bool DrawArea::createNewDrawing() {
  QImage blankDrawing;
  const QSize newSize(blankDrawing.size().expandedTo(size()));

  _mainDrawing = blankDrawing;

  ResizeCommand(this, &_mainDrawing, newSize).redo();
  _undoStack->clear();

  return true;
}
bool DrawArea::openDrawing(const QString &fileName) {
  QImage drawingToOpen;
  if (!drawingToOpen.load(fileName)) {
    return false;
  }

  const QSize newSize(drawingToOpen.size().expandedTo(size()));

  _mainDrawing = drawingToOpen;

  ResizeCommand(this, &_mainDrawing, newSize).redo();
  _undoStack->clear();

  return true;
}
bool DrawArea::saveDrawing(const QString &fileName, const char *fileFormat) {
  if (_mainDrawing.save(fileName, fileFormat)) {
    _undoStack->clear();
    return true;
  } else {
    return false;
  }
}

void DrawArea::setStrokeColor(const QColor &c) { _strokeColor = c; }
void DrawArea::setFillColor(const QColor &c) { _fillColor = c; }
void DrawArea::setPenWidth(int w) { _strokeWidth = w; }
void DrawArea::setDrawingFactory(DrawingFactory f) { _factory = f; }

void DrawArea::mousePressEvent(QMouseEvent *e) {
  if (e->button() == Qt::LeftButton && _factory) {
    _currentShape = _factory(e->pos(), _strokeWidth, _strokeColor, _fillColor);
  }
}
void DrawArea::mouseMoveEvent(QMouseEvent *e) {
  if ((e->buttons() & Qt::LeftButton) && _currentShape) {

    const QRect prevRect(_currentShape->rect());
    _currentShape->update(e->pos());

    update(_currentShape->rect().united(prevRect));
  }
}
void DrawArea::mouseReleaseEvent(QMouseEvent *e) {
  if (e->button() == Qt::LeftButton && _currentShape) {
    _undoStack->push(
        new DrawCommand(this, &_mainDrawing, std::move(_currentShape)));
  }
}

void DrawArea::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, true);

  const QRect drawnRectangle(event->rect());
  painter.drawImage(drawnRectangle, _mainDrawing, drawnRectangle);

  if (_currentShape) {
    _currentShape->draw(painter);
  }
}

void DrawArea::resizeEvent(QResizeEvent *event) {
  if (width() > _mainDrawing.width() || height() > _mainDrawing.height()) {
    const int newWidth(qMax(width() + 150, _mainDrawing.width()));
    const int newHeight(qMax(height() + 150, _mainDrawing.height()));
    const QSize newSize(newWidth, newHeight);

    if (isModified()) {
      _undoStack->push(new ResizeCommand(this, &_mainDrawing, newSize));
    } else {
      ResizeCommand(this, &_mainDrawing, newSize).redo();
    }
  }

  QWidget::resizeEvent(event);
}
} // namespace DrawApp

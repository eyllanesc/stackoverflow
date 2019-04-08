#include "command.h"

#include "drawarea.h"

namespace DrawApp {
/* Needed for merging */
enum CommandId { ResizeCommandId = 1 };

DrawCommand::DrawCommand(QWidget *drawArea, QImage *image,
                         std::unique_ptr<Shape> &&s)
    : _drawArea(drawArea), _image(image), _undoImage(image->copy(s->rect())),
      _shape(std::move(s)) {}

void DrawCommand::undo() {
  const QRect rect = _shape->rect();

  QPainter painter(_image);
  painter.drawImage(rect, _undoImage);

  _drawArea->update(rect);
}

void DrawCommand::redo() {
  QPainter painter(_image);
  _shape->draw(painter);

  _drawArea->update(_shape->rect());
}

FlipCommand::FlipCommand(QWidget *doc, QImage *image, bool horizontal,
                         bool vertical)
    : _drawArea(doc), _image(image), _horizontal(horizontal),
      _vertical(vertical) {}

void FlipCommand::undo() { redo(); }

void FlipCommand::redo() {
  *_image = _image->mirrored(_horizontal, _vertical);
  _drawArea->update();
}

ResizeCommand::ResizeCommand(QWidget *doc, QImage *image, const QSize &size)
    : _drawArea(doc), _image(image), _oldSize(image->size()), _newSize(size) {}

int ResizeCommand::id() const { return ResizeCommandId; }

bool ResizeCommand::mergeWith(const QUndoCommand *command) {
  if (command->id() != id())
    return false;

  /* Subsequent resize command will look like a single one:  keep the first
   * command's previous size and update it with the latest resize command's
   * new size.
   */
  _newSize = static_cast<const ResizeCommand *>(command)->_newSize;
  return true;
}

void ResizeCommand::undo() {
  *_image = _image->copy(0, 0, _oldSize.width(), _oldSize.height());
  _drawArea->update();
}

void ResizeCommand::redo() {
  if (_image->size() == _newSize) {
    return;
  }

  QImage newImage(_newSize, QImage::Format_RGB32);
  newImage.fill(Qt::white);

  QPainter painter(&newImage);
  painter.drawImage(QPoint(0, 0), *_image);
  *_image = newImage;

  _drawArea->update();
}

RotateCommand::RotateCommand(QWidget *doc, QImage *image, qreal deg)
    : _drawArea(doc), _image(image), _deg(deg) {}

void RotateCommand::undo() { rotate(-_deg); }

void RotateCommand::redo() { rotate(_deg); }

void RotateCommand::rotate(qreal deg) {
  QMatrix transf;
  *_image = _image->transformed(transf.rotate(deg));

  _drawArea->update();
}
} // namespace DrawApp

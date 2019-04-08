#ifndef _TROFIMOV_COMMAND_H_
#define _TROFIMOV_COMMAND_H_

#include "shape.h"

#include <QImage>
#include <QUndoCommand>
#include <QWidget>

#include <memory>
#include <vector>

namespace DrawApp {
class DrawCommand : public QUndoCommand {
  QWidget *_drawArea;
  QImage *_image;
  QImage _undoImage;
  std::unique_ptr<Shape> _shape;

public:
  explicit DrawCommand(QWidget *, QImage *, std::unique_ptr<Shape> &&);

  virtual void undo() override;
  virtual void redo() override;
};
class FlipCommand : public QUndoCommand {
public:
  explicit FlipCommand(QWidget *, QImage *, bool, bool);

  virtual void undo() override;
  virtual void redo() override;

private:
  QWidget *_drawArea;
  QImage *_image;

  bool _horizontal, _vertical;
};
class ResizeCommand : public QUndoCommand {
public:
  explicit ResizeCommand(QWidget *, QImage *, const QSize &);

  virtual int id() const override;
  virtual bool mergeWith(const QUndoCommand *) override;

  virtual void undo() override;
  virtual void redo() override;

private:
  QWidget *_drawArea;
  QImage *_image;

  QSize _oldSize, _newSize;
};
class RotateCommand : public QUndoCommand {
public:
  explicit RotateCommand(QWidget *, QImage *, qreal);

  virtual void undo() override;
  virtual void redo() override;

private:
  void rotate(qreal);

  QWidget *_drawArea;
  QImage *_image;

  qreal _deg;
};
} // namespace DrawApp

#endif

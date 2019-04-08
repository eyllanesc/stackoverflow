#pragma once

#include "RubberBand.h"
#include "UndoHistory.h"
#include <QGraphicsScene>

class ImageEditor {
public:
  ImageEditor(const QString &img);
  ~ImageEditor();

  void SetMaxPreviewSize(int w, int h);
  double PreviewZoom() const;
  void SetPreviewZoom(double zoom);
  void DrawPreview();
  void SaveToFile(const QString &path);

  void Rotate(double angle);
  void CropToSelection();
  void Resize(double zoom);
  void Resize(int w, int h);
  void ConvertToGrayscale(int threshold = -1);

  void Undo();
  void Redo();
  QSize Size();

  QGraphicsScene *previewScene;
  RubberBand rubberBand;

private:
  double previewZoom = 1;
  UndoHistory<QImage *> history;
  bool rubberBandInstalled = false;
};

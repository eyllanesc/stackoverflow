#include "ImageEditor.h"
#include "RubberBand.h"
#include <QGraphicsView>
#include <QImage>

ImageEditor::ImageEditor(const QString &path)
    : previewScene(new QGraphicsScene()), rubberBand(), history(5) {
  history.push(new QImage(path));
  if (history.current()->isNull())
    throw - 1;
}

ImageEditor::~ImageEditor() { delete previewScene; }

/**
 * @brief Draws image preview.
 */
void ImageEditor::DrawPreview() {
  previewScene->clear();

  // Actual image layer.
  auto image = new QGraphicsPixmapItem(QPixmap::fromImage(*history.current()));
  image->setAcceptHoverEvents(true);
  image->setScale(previewZoom);
  image->setTransformationMode(Qt::SmoothTransformation);

  // Layer with decorative half-transparent border.
  auto pixmapSize = image->pixmap().size();
  auto border =
      new QGraphicsRectItem(0, 0, pixmapSize.width(), pixmapSize.height());
  border->setScale(previewZoom);
  border->setPen(QPen(QColor(0, 0, 0, 64), 1, Qt::SolidLine, Qt::SquareCap,
                      Qt::RoundJoin));

  // Adds layers to scene.
  previewScene->addItem(image);
  previewScene->addItem(border);

  // Refresh selection.
  auto viewport = previewScene->views().first()->viewport();
  if (!rubberBandInstalled) {
    viewport->installEventFilter(&rubberBand);
  }

  rubberBand.SetPixmapItem(image);

  // Reset scene size to make scrollbars disappear.
  QPoint zero(0, 0);
  QRect rect(zero, history.current()->size() * previewZoom);
  previewScene->setSceneRect(rect);
}

/**
 * @brief Saves image to file on disk.
 * @param path Save path.
 */
void ImageEditor::SaveToFile(const QString &path) {
  history.current()->save(path);
}

/**
 * @brief Rotates image by given angle in degrees.
 */
void ImageEditor::Rotate(double angle) {
  QTransform transform;
  transform.rotate(angle);
  history.push(new QImage(
      history.current()->transformed(transform, Qt::SmoothTransformation)));
  DrawPreview();
}

/**
 * @brief Crops image to current selection.
 */
void ImageEditor::CropToSelection() {
  if (rubberBand.IsSelectionActive()) {
    history.push(
        new QImage(history.current()->copy(rubberBand.GetSelection())));
    DrawPreview();
  }
}

/**
 * @brief Scales image given amount of times.
 */
void ImageEditor::Resize(double zoom) {
  history.push(new QImage(history.current()->scaled(
      history.current()->size() * zoom, Qt::IgnoreAspectRatio,
      Qt::SmoothTransformation)));
  DrawPreview();
}

/**
 * @brief Scales image by fixed size.
 */
void ImageEditor::Resize(int w, int h) {
  history.push(new QImage(history.current()->scaled(w, h, Qt::IgnoreAspectRatio,
                                                    Qt::SmoothTransformation)));
  DrawPreview();
}

/**
 * @brief Converts image to greyscale.
 */
void ImageEditor::ConvertToGrayscale(int threshold) {
  // Convert to 32bit pixel format
  auto format = history.current()->hasAlphaChannel() ? QImage::Format_ARGB32
                                                     : QImage::Format_RGB32;

  auto dstImage = history.current()->convertToFormat(format);

  auto data = reinterpret_cast<unsigned int *>(dstImage.bits());
  auto pixelCount = dstImage.width() * dstImage.height();

  // Convert each pixel to grayscale
  for (auto i = 0; i < pixelCount; ++i) {
    auto val = qGray(*data);

    if (threshold != -1) {
      val = val > threshold ? 255 : 0;
    }

    *data = qRgba(val, val, val, qAlpha(*data));
    ++data;
  }

  history.push(new QImage(dstImage));
  DrawPreview();
}

/**
 * @brief Undoes last operation.
 */
void ImageEditor::Undo() {
  if (history.isUndoPossible()) {
    history.undo();
    DrawPreview();
  }
}

/**
 * @brief Redoes last operation.
 */
void ImageEditor::Redo() {
  if (history.isRedoPossible()) {
    history.redo();
    DrawPreview();
  }
}

/**
 * @brief Returns current image size in pixels.
 */
QSize ImageEditor::Size() { return history.current()->size(); }

/**
 * @brief Returns current preview zoom of image.
 */
double ImageEditor::PreviewZoom() const { return previewZoom; }

/**
 * @brief Sets image preview zoom.
 */
void ImageEditor::SetPreviewZoom(double zoom) {
  previewZoom = zoom;
  DrawPreview();
}

/**
 * @brief Sets fixed size of image preview.
 */
void ImageEditor::SetMaxPreviewSize(int w, int h) {
  auto size = history.current()->size();
  previewZoom = std::min(1.0 * w / size.width(), 1.0 * h / size.height());
  DrawPreview();
}

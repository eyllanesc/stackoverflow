#include "imageprovider.h"

#include <opencv2/opencv.hpp>

QImage convertMatToQImage(const cv::Mat &mat) {
  // 8-bits unsigned, NO. OF CHANNELS=1
  if (mat.type() == CV_8UC1) {
    // Set the color table (used to translate colour indexes to qRgb values)
    QVector<QRgb> colorTable;
    for (int i = 0; i < 256; i++)
      colorTable.push_back(qRgb(i, i, i));
    // Copy input Mat
    const uchar *qImageBuffer = (const uchar *)mat.data;
    // Create QImage with same dimensions as input Mat
    QImage img(qImageBuffer, mat.cols, mat.rows, mat.step,
               QImage::Format_Indexed8);
    img.setColorTable(colorTable);
    return img;
  }
  // 8-bits unsigned, NO. OF CHANNELS=3
  if (mat.type() == CV_8UC3) {
    // Copy input Mat
    const uchar *qImageBuffer = (const uchar *)mat.data;
    // Create QImage with same dimensions as input Mat
    QImage img(qImageBuffer, mat.cols, mat.rows, mat.step,
               QImage::Format_RGB888);
    return img.rgbSwapped();
  }
  return QImage();
}

ImageProvider::ImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image) {}

QImage ImageProvider::requestImage(const QString &id, QSize *size,
                                   const QSize &requestedSize) {
  Q_UNUSED(requestedSize)
  QUrl url(id);
  bool showEdited = url.query() == "edit=true";
  if (showEdited) {
    cv::Mat src = cv::imread(url.toLocalFile().toStdString());

    /// begin process
    cv::GaussianBlur(src, src, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
    cv::Mat grad_x, grad_y;
    cv::Mat abs_grad_x, abs_grad_y, src_gray, grad;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    cv::cvtColor(src, src_gray, CV_BGR2GRAY);
    /// Gradient X
    cv::Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta,
              cv::BORDER_DEFAULT);
    /// Gradient Y
    cv::Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta,
              cv::BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    /// end process
    QImage img = convertMatToQImage(grad);
    if (size)
      *size = QSize(img.width(), img.height());
    return img;
  } else {
    QImage img(url.toLocalFile());
    if (size)
      *size = QSize(img.width(), img.height());
    return img;
  }
}

#ifndef MATTOQIMAGE_H
#define MATTOQIMAGE_H

#include <QImage>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

static QImage MatToQImage(const cv::Mat &mat) {
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

#endif // MATTOQIMAGE_H

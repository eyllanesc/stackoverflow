#include "imageprovider.h"

#include <opencv2/opencv.hpp>

QImage convertMatToQImage(const cv::Mat &mat)
{
    // 8-bits unsigned, NO. OF CHANNELS=1
    if(mat.type()==CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    // 8-bits unsigned, NO. OF CHANNELS=3
    if(mat.type()==CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    return QImage();
}

ImageProvider::ImageProvider():
    QQuickImageProvider(QQuickImageProvider::Image){}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(requestedSize)
    QUrl url(id);
    bool showEdited = url.query() == "edit=true";
    if (showEdited) {
        cv::Mat src = cv::imread(url.toLocalFile().toStdString());
        cv::medianBlur(src, src, 5);
        QImage img = convertMatToQImage(src);
        if (size)
            *size = QSize(img.width(), img.height());
        return img;
    }
    else {
        QImage img(url.toLocalFile());
        if (size)
            *size = QSize(img.width(), img.height());
        return img;
    }
}



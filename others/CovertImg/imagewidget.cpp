#include "imagewidget.h"
#include <QWidget>
#include <QPainter>
#include <QDebug>

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{

}

QImage ImageWidget::image() const
{
    return mImage;
}

void ImageWidget::setImage(const QImage &image)
{
    mImage = image;
    update();
}

void ImageWidget::paintEvent(QPaintEvent *pe){
    QWidget::paintEvent(pe);
    QPainter painter(this);
    painter.drawImage(this->rect(), mImage);
}

QImage ImageWidget::OilPaint(const QImage &img, int radius, int levels)
{
    QImage img_out(img.width(),img.height(),img.format());

    QColor color;
    int imax, max;

    int red, green, blue, nCurIntensity;

    for(int y = radius; y < (img.height() -radius); y++){
        for(int x = radius; x < (img.width() -radius); x++){
            QVector<int> sumR(256);
            QVector<int> sumG(256);
            QVector<int> sumB(256);
            QVector<int> nIntensityCount(256);

            for(int ny=-radius; ny<= radius; ny++){
                for(int nx=-radius; nx<= radius; nx++){
                    color = img.pixel(x+nx,y+ ny);
                    red = color.red();
                    green = color.green();
                    blue = color.blue();
                    nCurIntensity = (((red + green + blue)/3.0)*levels)/255;
                    nCurIntensity = nCurIntensity > 255 ? 255: nCurIntensity;
                    nIntensityCount[nCurIntensity]++;
                    sumR[nCurIntensity] += red;
                    sumG[nCurIntensity] += green;
                    sumB[nCurIntensity] += blue;
                }
            }
            max = *std::max_element(nIntensityCount.constBegin() , nIntensityCount.constEnd());
            imax =nIntensityCount.indexOf(max);
            img_out.setPixel(x, y, qRgb(sumR[imax]/max, sumG[imax]/max, sumB[imax]/max));
        }
    }
    return img_out;

}

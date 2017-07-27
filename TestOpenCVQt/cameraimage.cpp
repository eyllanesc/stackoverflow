#include "cameraimage.h"
#include <QDebug>
#include <QPainter>

cameraimage::cameraimage(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
}

void cameraimage::startStreaming()
{
    qDebug() << "Starting Streaming";
    captureVideo.open(-1);
    if (captureVideo.isOpened() == false){
        qDebug() << "Camera can't open";
        return;
    }
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    timer->start(1);
}

void cameraimage::stopStreaming()
{
    captureVideo.release();
    timer->stop();
}

void cameraimage::paintEvent(QPaintEvent *)
{
    if(captureVideo.isOpened()){
        cv::Mat tmpImage;
        cv::Mat image;
        captureVideo.read(tmpImage);

        if (tmpImage.empty() == true){
            qDebug() << "EMPTY!";
            return;
        }

        cv::cvtColor(tmpImage, image, CV_BGR2RGB);
        QImage img((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);

        QPixmap pixmap = QPixmap::fromImage(img);
        QPainter painter(this);

        float comprimento = 1.0*width()/pixmap.width();
        float altura = 1.0*height()/pixmap.height();
        float ratio = 0.;

        if (comprimento<=altura)
            ratio = comprimento;
        else
            ratio = altura;

        QSize size = ratio*pixmap.size();
        size.setHeight(size.height()-10);

        QPoint p;
        p.setX(0 + (width()-size.width())/2);
        p.setY(5);
        painter.drawPixmap(QRect(p, size), pixmap.scaled(size, Qt::KeepAspectRatio));
    }
}

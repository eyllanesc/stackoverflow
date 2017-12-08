#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QPainter>
#include <QWidget>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr):QWidget(parent){}

    void setImage(const QImage &image){
        mImage = image;
        update();
    }
protected:
    void paintEvent(QPaintEvent *){
        QPainter painter(this);
        if(!mImage.isNull())
            painter.drawImage(QPoint(0, 0), mImage);
    }
private:
    QImage mImage;
};

#endif // PAINTWIDGET_H


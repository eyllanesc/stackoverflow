#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>

class ImageWidget : public QWidget
{
    Q_OBJECT
    QImage mImage;
protected:
    void virtual paintEvent(QPaintEvent *);
public:
    explicit ImageWidget(QWidget *parent = 0);
    static QImage OilPaint(const QImage &img, int radius, int levels);
    QImage image() const;
    void setImage(const QImage &image);
};

#endif // IMAGEWIDGET_H

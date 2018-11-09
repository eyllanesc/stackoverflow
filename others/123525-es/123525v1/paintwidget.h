#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QPainter>
#include <QWidget>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr):QWidget(parent){}
protected:
    void paintEvent(QPaintEvent *){
        QPainter painter(this);
        QPen lapiz;
        lapiz.setColor(QColor(Qt::black));
        lapiz.setWidthF(2.5);
        painter.setPen(lapiz);
        painter.drawEllipse(15, 15, 10, 10);
    }
};

#endif // CUSTOMWIDGET_H

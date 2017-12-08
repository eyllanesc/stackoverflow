#include "widget.h"
#include "ui_widget.h"

#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QImage image(ui->widget->size(), QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);
    QPainter  auxPainter(&image);
    QPen lapiz;
    lapiz.setColor(QColor(Qt::black));
    lapiz.setWidthF(2.5);
    auxPainter.setPen(lapiz);
    auxPainter.drawEllipse(15, 15, 10, 10);
    ui->widget->setImage(image);

}

Widget::~Widget()
{
    delete ui;
}

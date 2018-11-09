#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsItem>
#include <QGraphicsView>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(0, 0, 200, 200));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QPainterPath path;
    path.moveTo(10, 20);
    path.lineTo(10, 40);
    path.arcTo(QRectF(10, 20, 40, 40), 180, 180);
    path.moveTo(50, 40);
    path.lineTo(50, 20);
    QPen redPen(Qt::red);
    redPen.setWidth(2);
    QGraphicsPathItem* item = ui->graphicsView->scene()->addPath(path, redPen);
    /*
        QGraphicsPathItem* item = new QGraphicsPathItem(path);
        item->setPen(redPen);
    */

    item->setFlag(QGraphicsItem::ItemIsMovable, true);
    item->setFlag(QGraphicsItem::ItemIsSelectable,true);
}

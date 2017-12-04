#include "widget.h"
#include "ui_widget.h"
#include "dgraphicsitem.h"

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush brush(Qt::white);
    QPen pen(Qt::green);
    pen.setWidth(1);

    DGraphicsEllipseItem* ellipse = new DGraphicsEllipseItem(QRectF(20,20, 200,100), 10);
    scene->addItem(ellipse);
    ellipse->setPen(pen);
    ellipse->setBrush(brush);
    ellipse->setFlag(QGraphicsItem::ItemIsMovable, true);

    DGraphicsRectItem* rect = new DGraphicsRectItem(QRectF(-20,-10,200,100), 10);
    scene->addItem(rect);
    rect->setPen(pen);
    rect->setBrush(brush);
    rect->setFlag(QGraphicsItem::ItemIsMovable, true);
}

Widget::~Widget()
{
    delete ui;
}

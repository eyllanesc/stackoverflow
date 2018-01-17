#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>
#include <QVariantAnimation>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(-100, -100, 200, 200));

    QGraphicsRectItem *r = ui->graphicsView->scene()->addRect(0, 0, 60, 60, QPen(Qt::blue), QBrush(Qt::red));
    r->setTransformOriginPoint(r->rect().center());

    QVariantAnimation *animation = new QVariantAnimation(this);
    connect(animation, &QVariantAnimation::valueChanged, [r](QVariant value){
        r->setRotation(value.toReal());
    });
    animation->setStartValue(0);
    animation->setEndValue(360);
    animation->setDuration(1000);
    animation->setLoopCount(-1);
    animation->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

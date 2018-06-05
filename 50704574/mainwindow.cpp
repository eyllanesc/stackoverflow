#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsPixmapItem>
#include "customrect.h"
#include "myarrow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(this);
    view->setFixedSize(600,500);
    view->setScene(scene);

    CustomRect *rect = new CustomRect(QRectF(50,50,100,100));
    scene->addItem(rect);

    MyArrow *arrow = new MyArrow(rect);

    rect->addLine(arrow);
    scene->addItem(arrow);
    rect->addLine(arrow);
}


MainWindow::~MainWindow()
{
    delete ui;
}

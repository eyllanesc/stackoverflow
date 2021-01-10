#include "arrow.h"
#include "component.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    // ui->graphicsView->setSceneRect(QRectF(0, 0, 512, 512));

    QGraphicsScene *scene = ui->graphicsView->scene();

    Component *comp1 = new Component;
    Component *comp2 = new Component;

    comp1->setPos(50, 50);
    comp2->setPos(400, 400);

    Arrow *arrow = new Arrow(comp1, comp2);
    scene->addItem(comp1);
    scene->addItem(comp2);
    scene->addItem(arrow);
}

MainWindow::~MainWindow()
{
    delete ui;
}


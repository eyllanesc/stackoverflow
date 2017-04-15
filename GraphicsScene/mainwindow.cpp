#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStatusBar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qApp->installEventFilter(this);

    // A way to close the app, clicking actionQuit, without using a seperate function
    //    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    int Width = 3200;
    int Height = 1600;
    this->resize(Width, Height);
    scene = new GraphicsScene();
    ui->graphicsView->setScene(scene);
    int sceneWidth = this->width()-20;
    int sceneHeight = this->height()-160;
    ui->graphicsView->resize(sceneWidth, sceneHeight);
    ui->graphicsView->setSceneRect(0, 0, sceneWidth, sceneHeight);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);
    ui->graphicsView->scale(1, -1); // Coordinate 0,0 at Bottom-Left

    statusBar()->showMessage(QString("Size: %1, %2 ").arg(Width).arg(Height));

    scene->setBackgroundBrush(Qt::black);

    connect(scene, &GraphicsScene::changedMousePosition, this, &MainWindow::onChangedMousePosition);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onChangedMousePosition(QPointF point)
{
    qDebug()<< scene->getMousePoint();
    statusBar()->showMessage(QString("x: %1 y: %2").arg(point.x()).arg(point.y()));
}


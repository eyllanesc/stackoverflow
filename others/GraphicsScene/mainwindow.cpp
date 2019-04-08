#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  qApp->installEventFilter(this);

  Count = 0;
  // A way to close the app, clicking actionQuit, without using a seperate
  // function
  //    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

  int Width = 3200;
  int Height = 1600;
  this->resize(Width, Height);
  scene = new GraphicsScene;
  ui->graphicsView->setScene(scene);
  int sceneWidth = this->width() - 20;
  int sceneHeight = this->height() - 160;
  ui->graphicsView->resize(sceneWidth, sceneHeight);
  ui->graphicsView->setSceneRect(0, 0, sceneWidth, sceneHeight);
  //    ui->graphicsView->setRenderHints(QPainter::Antialiasing |
  //    QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);
  ui->graphicsView->scale(1, -1); // Coordinate 0,0 at Bottom-Left

  statusBar()->showMessage(QString("Size: %1, %2 ").arg(Width).arg(Height));

  // Create a timer
  timer = new QTimer(this);
  // Setup signal and slot
  connect(timer, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));
  // Setup interval in msec
  timer->start(100);

  scene->setBackgroundBrush(Qt::black);

  //    connect(scene, SIGNAL(GraphicsScene::changedMousePosition(QPointF
  //    mousePoint)), this, SLOT(MainWindow::onChangedMousePosition(QPointF
  //    mousePoint)));

  connect(scene, &GraphicsScene::changedMousePosition, this,
          &MainWindow::onChangedMousePosition);
  connect(scene, &GraphicsScene::changedNumber, this,
          &MainWindow::onChangedNumber);

  ui->label->setText(QString("hello"));
  ui->graphicsView->setMouseTracking(true);

  scene->setNumber(0);
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
  Q_UNUSED(obj)
  if (event->type() == QEvent::MouseMove) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    statusBar()->showMessage(QString("Mouse move (%1,%2)")
                                 .arg(mouseEvent->pos().x())
                                 .arg(mouseEvent->pos().y()));
  }
  return false;
}

void MainWindow::eraseScreen(void) {
  QColor color;
  color.setRgb(0, 0, 0);
  QPen pen;
  pen.setColor(color);
  pen.setWidth(1);
  QBrush brush;
  brush.setColor(color);
  brush.setStyle(Qt::SolidPattern);

  scene->addRect(0, 0, width() + 1000, height() + 1000, pen, brush);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  Q_UNUSED(event)
  int sceneWidth = this->width() - 20;
  int sceneHeight = this->height() - 160;
  ui->graphicsView->resize(sceneWidth, sceneHeight);
  ui->graphicsView->setSceneRect(0, 0, sceneWidth - 1, sceneHeight - 1);
  // rubberband->setRect(ui->graphicsView->sceneRect());
}

void MainWindow::on_toolButtonDraw_clicked() {
  //    Line myLine;
  scene->myLine(100, 100, 1500, 500);

  //    // Just draw something by clicking a button
  //    QColor color;
  //    color.setRgb(128, 0, 255);
  //    QPen pen;
  //    pen.setColor(color);
  //    pen.setWidth(20);
  //    pen.setCapStyle(Qt::RoundCap);
  //    scene->addLine(300, 100, 500, 300, pen);
  //    scene2->addLine(100, 100, 300, 300, pen);
}

void MainWindow::on_toolButtonErase_clicked() { eraseScreen(); }

void MainWindow::on_actionQuit_triggered() {
  // A way to close the app, clicking actionQuit, using this function
  // Some cleanup is possible here
  close();
}

void MainWindow::MyTimerSlot() {
  //    GraphicsScene *graphicsScene = new GraphicsScene();
  //    QPointF mousePoint = graphicsScene->getMousePoint();

  //    GraphicsScene graphicsScene; //Create instance
  //    QPointF mousePoint = scene->getMousePoint();

  //    int MouseX   = scene->getMouseX();
  //    int MouseY   = scene->getMouseY();
  int myNumber = scene->getNumber();
  //    qDebug() << "Timer..." << QString("Mouse: %1,
  //    %2").arg(mousePoint.x()).arg(mousePoint.y()); qDebug() << "Timer..." <<
  //    QString("Mouse: %1, %2").arg(MouseX).arg(MouseY); qDebug() << "Timer..."
  //    << QString("Number: %1").arg(myNumber);
  //    statusBar()->showMessage(QString("x,y: %1,
  //    %2").arg(mousePoint.x()).arg(mousePoint.y()));
  //    ui->label->setText(QString("%1").arg(myNumber));
}

void MainWindow::onChangedMousePosition(QPointF mousePoint) {
  //    statusBar()->showMessage(QString("x: %1 y:
  //    %2").arg(mousePoint.x()).arg(mousePoint.y()));
  statusBar()->showMessage(
      QString("x,y: %1, %2").arg(mousePoint.x()).arg(mousePoint.y()));
}

void MainWindow::onChangedNumber(int Number) {
  //    statusBar()->showMessage(QString("x: %1 y:
  //    %2").arg(mousePoint.x()).arg(mousePoint.y()));
  ui->label->setText(QString("N: %1").arg(Number));
}

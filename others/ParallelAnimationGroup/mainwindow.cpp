#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mygraphicsrectitem.h"

#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  scene = new QGraphicsScene;
  ui->graphicsView->setScene(scene);

  int colWidth = 50;
  int spaceWidth = 25;
  int anchorID = 5;

  group = new QParallelAnimationGroup;
  for (int i = 0; i < 10; i += 1) {
    MyGraphicsRectItem *temp = new MyGraphicsRectItem(0, 0, 100, 100);
    scene->addItem(temp);
    QPropertyAnimation *anim = new QPropertyAnimation(temp, "position");
    anim->setDuration(5000);
    anim->setStartValue(temp->pos());
    QPropertyAnimation *geo = new QPropertyAnimation(temp, "geometry");
    geo->setDuration(5000);
    geo->setStartValue(temp->rect());
    geo->setEndValue(QRectF(0, 0, colWidth, -80));
    if (i > anchorID) {
      anim->setEndValue(QPointF(40 + spaceWidth * (i) + colWidth * (i - 1),
                                ui->graphicsView->height() - 40));
    } else {
      anim->setEndValue(QPointF(40 + spaceWidth * (i + 1) + colWidth * (i),
                                ui->graphicsView->height() - 40));
    }
    group->addAnimation(geo);
    group->addAnimation(anim);
  }
  group->start(QAbstractAnimation::DeleteWhenStopped);
}

MainWindow::~MainWindow() { delete ui; }

#include "mainwindow.h"
#include "grafica_ppu.h"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>
#include <QVariantAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->graphicsView->setScene(new QGraphicsScene(-100, -100, 200, 200));

  /*QGraphicsRectItem *r = ui->graphicsView->scene()->addRect(0, 0, 40, 40,
  QPen(Qt::blue)); r->setTransformOriginPoint(r->rect().center());

  QVariantAnimation *animation = new QVariantAnimation(this);
  connect(animation, &QVariantAnimation::valueChanged, [r](QVariant value){
      r->setRotation(value.toReal());
  });
  animation->setStartValue(0);
  animation->setEndValue(360);
  animation->setDuration(1000);
  animation->setLoopCount(-1);
  animation->start();*/

  GraphicModuleData tmp{0, 0, 40, 40};
  Grafica_PPU *item = new Grafica_PPU("test", tmp, QPen(Qt::red), 100);

  GraphicModuleData tmp2{-50, 50, 60, 40};
  Grafica_PPU *item2 = new Grafica_PPU("test", tmp2, QPen(Qt::red), 90);

  ui->graphicsView->scene()->addItem(item);
  ui->graphicsView->scene()->addItem(item2);
}

MainWindow::~MainWindow() { delete ui; }

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPropertyAnimation>

#include "mycircle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  auto scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  auto c = new MyCircle;
  scene->addItem(c);

  auto animationBoutonRondTaille = new QPropertyAnimation(c, "geometry");
  animationBoutonRondTaille->setDuration(1000);
  animationBoutonRondTaille->setKeyValueAt(0, QRect(-100, -100, 200, 200));
  animationBoutonRondTaille->setKeyValueAt(0.5, QRect(-80, -80, 160, 160));
  animationBoutonRondTaille->setKeyValueAt(1, QRect(-100, -100, 200, 200));
  animationBoutonRondTaille->start();
}

MainWindow::~MainWindow() { delete ui; }

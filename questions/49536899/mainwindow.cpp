#include "mainwindow.h"
#include "block.h"
#include "ui_mainwindow.h"

#include "graphicsscene.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  scene = new GraphicsScene;
  ui->graphicsView->setScene(scene);
  for (int row = -4; row < 8; ++row)
    for (int column = 0; column < 4; ++column) {
      Block *b = new Block;
      scene->addItem(b);
      b->setPos(row * 95, column * 85);
    }
}
MainWindow::~MainWindow() { delete ui; }

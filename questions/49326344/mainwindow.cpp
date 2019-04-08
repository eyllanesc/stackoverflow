#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>

MainWindow *MainWindow::mInstance = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
}

MainWindow *MainWindow::instance(QWidget *parent) {
  if (mInstance == NULL)
    mInstance = new MainWindow(parent);
  return mInstance;
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::drawConnection() {
  QFont seriFont("Times", 30, QFont::Bold);
  connection = scene->addText("Client is connecting", seriFont);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  button = new QPushButton("test", ui->customPlot);

  QVector<double> x(101), y(101); // initialize with entries 0..100
  for (int i = 0; i < 101; ++i) {
    x[i] = i / 50.0 - 1; // x goes from -1 to 1
    y[i] = x[i] * x[i];  // let's plot a quadratic function
  }
  // create graph and assign data to it:
  ui->customPlot->addGraph();
  ui->customPlot->graph(0)->setData(x, y);
  // give the axes some labels:
  ui->customPlot->xAxis->setLabel("x");
  ui->customPlot->yAxis->setLabel("y");
  // set axes ranges, so we see all data:
  ui->customPlot->xAxis->setRange(-1, 1);
  ui->customPlot->yAxis->setRange(0, 1);
  ui->customPlot->replot();
}

void MainWindow::moveButtonFromCoord() {
  double real_x = ui->customPlot->xAxis->coordToPixel(0);
  double real_y = ui->customPlot->yAxis->coordToPixel(0);
  QRect geo = button->geometry();
  geo.moveCenter(QPoint(real_x, real_y));
  button->setGeometry(geo);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
  moveButtonFromCoord();
  QMainWindow::resizeEvent(event);
}

void MainWindow::showEvent(QShowEvent *event) {
  moveButtonFromCoord();
  QMainWindow::showEvent(event);
}

MainWindow::~MainWindow() { delete ui; }

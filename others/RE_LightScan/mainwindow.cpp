#include "mainwindow.h"
#include "lscurve.h"
#include "lsplot.h"
#include "luck.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  isZoomingActived = false;
  isGrabActived = false;
  ui->tabWidget->setStyleSheet("QTabWidget::pane { border: 0; }");

  plot->setParent(ui->widSpecPlot);
  LSCurve *cOne = plot->newCurve("Demo Curve", Qt::red, 2);
  std::fstream datafile;
  datafile.open("96e79667-c26d-48ed-8687-7d83796c35bf.txt", std::ios::in);
  if (DEBUG) {
    int numx;
    double numy;
    int i = 0;
    char buf[32];
    if (datafile.is_open()) {
      while (!datafile.eof()) {
        datafile.getline(buf, 32);
        while (buf[++i] != '\t')
          ;
        buf[i] = 0;
        numx = atoi(buf);
        numy = atof(&buf[++i]);
        i = 0;
        cOne->addPoint(numx, numy);
        cOne->reDraw();
      }
    }
  }
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::disableAll() {
  plot->zoomer->setEnabled(false);
  plot->magnifier->setEnabled(false);
  plot->panner->setEnabled(false);
  isZoomingActived = false;
  isGrabActived = false;
  plot->setCurve(false);
  ui->tbZoom->setChecked(false);
  ui->tbPan->setChecked(false);

  return true;
}

void MainWindow::zooming() {
  if (isZoomingActived) {
    plot->zoomer->setEnabled(false);
    plot->magnifier->setEnabled(false);
    isZoomingActived = false;
  } else {
    disableAll();
    plot->zoomer->setEnabled(true);
    plot->magnifier->setEnabled(true);
    plot->magnifier->setMouseButton(
        Qt::NoButton); //关闭右键缩放功能, 避免功能重复.
    ui->tbZoom->setChecked(true);
    isZoomingActived = true;
  }
}

void MainWindow::grab() {
  if (isGrabActived) {
    disableAll();

  } else {
    disableAll();
    plot->setCurve(true);
    plot->panner->setEnabled(true);
    ui->tbPan->setChecked(true);
    isGrabActived = true;
  }
}

void MainWindow::autoScale() {
  plot->plot->setAxisAutoScale(QwtPlot::yLeft, true);
  plot->rePlot();
}
void MainWindow::reinitialScale() { plot->initialScale(); }

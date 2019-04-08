#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QLineSeries *series0 = new QLineSeries();
  QLineSeries *series1 = new QLineSeries();

  *series0 << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7)
           << QPointF(12, 6) << QPointF(16, 7) << QPointF(18, 5);
  *series1 << QPointF(1, 3) << QPointF(3, 4) << QPointF(7, 3) << QPointF(8, 2)
           << QPointF(12, 3) << QPointF(16, 4) << QPointF(18, 3);

  QAreaSeries *series = new QAreaSeries(series0, series1);
  series->setName("Batman");
  QPen pen(0x059605);
  pen.setWidth(3);
  series->setPen(pen);

  QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
  gradient.setColorAt(0.0, 0x3cc63c);
  gradient.setColorAt(1.0, 0x26f626);
  gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
  series->setBrush(gradient);

  QChart *chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("Simple areachart example");
  chart->createDefaultAxes();
  chart->axisX()->setRange(0, 20);
  chart->axisY()->setRange(0, 10);

  ui->chartview->setChart(chart);
}

MainWindow::~MainWindow() { delete ui; }

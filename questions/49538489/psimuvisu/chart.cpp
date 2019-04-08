#include "chart.h"
#include <QQueue>
#include <QtCharts>

// Utilitaire
//    this->yValue = QRandomGenerator::global()->bounded(5) - 2.5;
//    float axisXMin =
//    (qobject_cast<QValueAxis*>(this->qChart->axisX()))->min();

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags),
      qlsSeries(new QLineSeries(this)), qZoomAera(new QRectF),
      qQueue(new QQueue<float>), xValue(0), yValue(0) {
  this->noZoom = true;
  this->zoom = 0;
  this->positionZoom = 0.2;
  this->pauseValue = true;

  this->qtimer.setInterval(100);

  this->addSeries(this->qlsSeries);
  this->createDefaultAxes();
  this->vaAxisX = qobject_cast<QValueAxis *>(this->axisX());
  this->vaAxisY = qobject_cast<QValueAxis *>(this->axisY());
  this->vaAxisX->setRange(0, 10);
  this->xDelta = 10;
  this->vaAxisY->setRange(-10, 10);
  this->vaAxisX->setTickCount(10);
  this->vaAxisY->setTickCount(5);
  this->xWidthAera = 0;

  QPen p = this->qlsSeries->pen();
  p.setWidth(1);
  this->qlsSeries->setPen(p);
  this->qlsSeries->setUseOpenGL(true);

  this->setTitle("Dynamic chart");
  this->legend()->hide();
  this->setAnimationOptions(QChart::NoAnimation);
  this->setMargins(QMargins(0, 0, 0, 0));
  this->setContentsMargins(0, 0, 0, 0);
  this->setBackgroundRoundness(0);
  //    this->setPlotAreaBackgroundBrush(QBrush(Qt::darkCyan,
  //    Qt::Dense3Pattern)); this->setBackgroundBrush(QBrush(Qt::darkCyan,
  //    Qt::SolidPattern));

  this->setZoom(0);
  this->setPosition(0.2);

  QObject::connect(&this->qtimer, &QTimer::timeout, this,
                   &Chart::handleTimeout);

  this->qtimer.start();
}

Chart::~Chart() {}

void Chart::addValue(float val) { this->qQueue->enqueue(val); }

void Chart::setZoom(float scaledZoom) {
  this->zoom = scaledZoom;
  this->refreshAxis();
}

void Chart::resetZoom() { this->zoomReset(); }

void Chart::zoomInRubberBand() {
  qDebug() << "(zoomInRubberBand): axisMax: "
           << QString::number(this->vaAxisX->max());
  qDebug() << "(zoomInRubberBand): axisMin: "
           << QString::number(this->vaAxisX->min());
}

void Chart::setPosition(float positionZoom) {
  this->positionZoom = positionZoom;
  this->refreshAxis();
}

void Chart::setPause(bool p) { this->pauseValue = p; }

void Chart::handleTimeout() {
  while (this->qQueue->isEmpty() == false) {
    this->refreshAxis();
    this->qlsSeries->append(this->xValue++, this->qQueue->dequeue());
  }
}

void Chart::resizeEvent(QResizeEvent *event) {
  //    QChart::resizeEvent(event);
}

void Chart::refreshAxis() {
  float rangeMin = this->xValue * this->zoom;
  float rangeMax = this->xValue;
  float deltaRange = rangeMax - rangeMin;
  rangeMin = rangeMin + (deltaRange * this->positionZoom);
  rangeMax = rangeMax + (deltaRange * this->positionZoom);
  this->vaAxisX->setRange(rangeMin, rangeMax);
}

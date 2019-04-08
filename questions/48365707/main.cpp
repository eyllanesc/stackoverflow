#include "qcustomplot.h"

#include <QApplication>

#include <QTimer>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QCustomPlot *_myPlot = new QCustomPlot;
  _myPlot->resize(640, 480);

  // some data
  QVector<double> x;
  QVector<double> y;

  for (int point = 0; point < 100; point++) {
    x << point;
    y << 80 * qSin(point * 0.1);
  }

  QCPGraph *newCurve = new QCPGraph(_myPlot->xAxis, _myPlot->yAxis);
  newCurve->addData(x, y);

  QBrush shadowBrush(QColor(0, 0, 0), Qt::Dense7Pattern);

  newCurve->setBrush(shadowBrush);

  QCPGraph *minGraph = new QCPGraph(_myPlot->xAxis, _myPlot->yAxis);
  newCurve->setChannelFillGraph(minGraph);

  QObject::connect(
      _myPlot->xAxis,
      static_cast<void (QCPAxis::*)(const QCPRange &)>(&QCPAxis::rangeChanged),
      [_myPlot, minGraph](const QCPRange &newRange) {
        minGraph->setData(QVector<double>{newRange.lower, newRange.upper},
                          QVector<double>{_myPlot->yAxis->range().lower,
                                          _myPlot->yAxis->range().lower});
      });

  QObject::connect(
      _myPlot->yAxis,
      static_cast<void (QCPAxis::*)(const QCPRange &)>(&QCPAxis::rangeChanged),
      [_myPlot, minGraph](const QCPRange &newRange) {
        minGraph->setData(QVector<double>{_myPlot->xAxis->range().lower,
                                          _myPlot->xAxis->range().upper},
                          QVector<double>{newRange.lower, newRange.lower});
      });

  // test

  _myPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                           QCP::iSelectAxes | QCP::iSelectLegend |
                           QCP::iSelectPlottables);
  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, [&_myPlot]() {
    QCPRange range = _myPlot->yAxis->range();
    range.lower -= 1;
    _myPlot->yAxis->setRange(range);
    _myPlot->replot();
  });

  timer.start(100);
  _myPlot->rescaleAxes();
  _myPlot->show();
  return a.exec();
}

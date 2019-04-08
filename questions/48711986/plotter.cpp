#include "plotter.h"
#include <QPainter>
#include <random>

#include <QDebug>

plotter::plotter(QWidget *parent) : QwtPlot(parent) {

  direct_painter = new QwtPlotDirectPainter(this);
  setAutoReplot(false);
  setCanvas(new QwtPlotCanvas());

  curve = new QwtPlotCurve("Test c");
  curve->setPen(Qt::white);
  curve->setData(new CurveData());
  curve->setStyle(QwtPlotCurve::Lines);
  curve->setSymbol(NULL);
  curve->attach(this);

  setAxisScale(yLeft, 0, 10, 0.5);
  setAxisScale(xBottom, 0, 1000, 100);

  replot();
}

void plotter::add_point(const QPointF &p) {
  qDebug() << p;
  CurveData *data = static_cast<CurveData *>(curve->data());
  data->append(p);
  /* This call should be
   * direct_painter->drawSeries(curve, data->size() - 1, data->size() -1);
   * but this doesn't work as in the examples
   */
  direct_painter->drawSeries(curve, 0, data->size() - 1);
}

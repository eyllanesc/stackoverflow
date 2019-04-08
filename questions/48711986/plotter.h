#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>

#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_dict.h>
#include <qwt_plot_directpainter.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>

class CurveData : public QwtArraySeriesData<QPointF> {
public:
  CurveData() {}

  virtual QRectF boundingRect() const {
    if (d_boundingRect.width() < 0.0)
      d_boundingRect = qwtBoundingRect(*this);

    return d_boundingRect;
  }

  inline void append(const QPointF &point) { d_samples += point; }

  void clear() {
    d_samples.clear();
    d_samples.squeeze();
    d_boundingRect = QRectF(0.0, 0.0, -1.0, -1.0);
  }
};

class plotter : public QwtPlot {
  Q_OBJECT
public:
  plotter(QWidget *parent = nullptr);

public slots:
  void add_point(const QPointF &p);

private:
  QwtPlotCurve *curve{nullptr};
  QwtPlotDirectPainter *direct_painter;
};

#endif // PLOTTER_H

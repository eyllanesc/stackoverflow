#include "lsplot.h"
#include "lscurve.h"
#include "luck.h"
#include <QMainWindow>

#include <qwt_picker_machine.h>

#include <QDebug>

LSPlot::LSPlot(QString PlotName, enum Qt::GlobalColor bgColor, QObject *parent)
    : QObject(parent) {
  plot->setTitle(PlotName);
  plot->setCanvasBackground(bgColor);
  initialScale();

  grid->attach(this->plot);

  zoomer = new QwtPlotZoomer(plot->canvas()); //矩形缩放
  zoomer->setEnabled(false);
  panner = new QwtPlotPanner(plot->canvas()); //鼠标平移
  panner->setEnabled(false);
  magnifier = new QwtPlotMagnifier(plot->canvas()); //滚轮缩放
  magnifier->setEnabled(false);
  // picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
  // plot->canvas());
  QwtPlotPicker *plotPicker = new QwtPlotPicker(
      this->plot->xBottom, this->plot->yLeft, QwtPicker::CrossRubberBand,
      QwtPicker::AlwaysOn, this->plot->canvas());
  QwtPickerMachine *pickerMachine = new QwtPickerClickPointMachine();
  plotPicker->setStateMachine(pickerMachine);

  connect(plotPicker, SIGNAL(selected(const QPointF &)), this,
          SLOT(onSelected(const QPointF &)));
}

LSCurve *LSPlot::newCurve(QString CurveName, const QColor &PenColor,
                          qreal PenWidth) {
  LSCurve *curve = new LSCurve;
  curve->QwtCurve->setTitle(CurveName);
  curve->QwtCurve->setPen(PenColor, PenWidth);
  curve->QwtCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true); //反锯齿
  // curve->QwtCurve->setCurveAttribute(QwtPlotCurve::Fitted, true);//平滑曲线
  curve->QwtCurve->attach(this->plot);
  return curve;
}

bool LSPlot::setParent(QWidget *parent) {
  Layout->addWidget(plot);
  // plot->setParent(parent);
  parent->setLayout(Layout);
  return true;
}

bool LSPlot::setCurve(bool state) {
  if (state) {
    plot->canvas()->setCursor(QCursor(Qt::ClosedHandCursor));
  } else {
    plot->canvas()->setCursor(QCursor(Qt::CrossCursor));
  }
  return true;
}

bool LSPlot::rePlot() {
  plot->replot();
  return true;
}

void LSPlot::onSelected(const QPointF &pos) { qDebug() << pos; }

bool LSPlot::initialScale() {
  plot->setAxisScale(QwtPlot::xBottom, 0, 2048);
  plot->setAxisScale(QwtPlot::yLeft, 0, 65535);
  rePlot();
  return true;
}

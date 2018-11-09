#ifndef LSPLOT_H
#define LSPLOT_H
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_picker.h>
#include <QGridLayout>
#include "lscurve.h"


class LSPlot: public QObject{
    Q_OBJECT
public:
    QwtPlot *plot = new QwtPlot;
    LSPlot(QString PlotName, enum Qt::GlobalColor bgColor, QObject *parent=0);
    int             setBackgroundColor(Qt::GlobalColor);
    LSCurve         *newCurve(QString CurveName, const QColor& PenColor, qreal PenWidth);
    bool            setParent(QWidget *parent);
    QwtPlotZoomer   *zoomer;
    QwtPlotPanner *panner;
    QwtPlotMagnifier *magnifier;
    QwtPlotPicker *picker;
    bool setCurve(bool state);
    bool initialScale();
    bool rePlot();
private:
    QwtPlotGrid *grid = new QwtPlotGrid();
    QGridLayout *Layout = new QGridLayout();

private slots:
    void onSelected(const QPointF&pos);

};

#endif // LSPLOT_H

#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts>
#include <QChartView>

class ChartView : public QChartView
{
public:
    ChartView(QWidget *parent = Q_NULLPTR);
    ChartView(QChart *chart, QWidget *parent = Q_NULLPTR);

protected:
    void showEvent(QShowEvent * event);
};

#endif // CHARTVIEW_H

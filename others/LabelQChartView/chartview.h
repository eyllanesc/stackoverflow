#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>
#include <QtCharts>

class ChartView : public QChartView {
public:
  ChartView(QWidget *parent = Q_NULLPTR);
  ChartView(QChart *chart, QWidget *parent = Q_NULLPTR);

protected:
  void showEvent(QShowEvent *event);
  void resizeEvent(QResizeEvent *event);

  QList<QGraphicsTextItem *> textItems;

private:
  void drawLabels();
};

#endif // CHARTVIEW_H

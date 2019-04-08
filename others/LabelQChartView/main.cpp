#include <QApplication>

#include <QtCharts>

#include "chartview.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QLineSeries *series = new QLineSeries();

  series->append(0, 6);
  series->append(2, 4);
  series->append(3, 8);
  series->append(7, 4);
  series->append(10, 5);

  QChart *chart = new QChart();
  chart->legend()->hide();
  chart->addSeries(series);
  chart->createDefaultAxes();
  chart->setTitle("Simple line chart example");

  ChartView *chartView = new ChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QMainWindow window;
  window.setCentralWidget(chartView);

  window.resize(400, 300);
  window.show();
  return a.exec();
}

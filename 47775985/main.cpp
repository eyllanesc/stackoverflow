#include <QApplication>
#include <QChartView>
#include <QLineSeries>

#include <QDebug>

QtCharts::QLineSeries *convertLine2Step(const QtCharts::QLineSeries* series){
    QtCharts::QLineSeries *s = new QtCharts::QLineSeries;
    *s<<series->at(0);
    int x, y;
    for(int i=1; i < series->count(); i++){
        x = series->at(i).x();
        y = series->at(i-1).y();
        *s<<QPointF(x, y);
        *s <<series->at(i);
    }
    return s;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtCharts::QChartView w;
    w.setRenderHint(QPainter::Antialiasing);
    QtCharts::QChart chart;
    chart.legend()->setVisible(true);
    w.setChart(&chart);
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries;
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
    series->setName("original");
    QtCharts::QLineSeries *stepSerie = convertLine2Step(series);
    stepSerie->setName("step");
    chart.addSeries(series);
    chart.addSeries(stepSerie);
    chart.createDefaultAxes();
    chart.setTitle("Simple line chart example");
    w.show();
    return a.exec();
}

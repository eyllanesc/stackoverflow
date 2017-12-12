#include <QApplication>
#include <QChartView>
#include <QLineSeries>

#include <QDebug>

QVector<QPointF> convertLine2Step(const QVector<QPointF> &points){
    QVector<QPointF> s;
    s<<points.at(0);
    int x, y;
    for(int i=1; i < points.count(); i++){
        x = points.at(i).x();
        y = points.at(i-1).y();
        s<<QPointF(x, y);
        s <<points.at(i);
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
    QVector<QPointF> points;
    points<<QPointF(2, 4);
    points<<QPointF(3, 8);
    points<<QPointF(7, 4);
    points<<QPointF(10, 5);
    points << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    *series<< points.toList();
    series->setName("original");

    QtCharts::QLineSeries *stepSerie = new QtCharts::QLineSeries;
    *stepSerie<<convertLine2Step(points).toList();
    stepSerie->setName("step");
    chart.addSeries(series);
    chart.addSeries(stepSerie);
    chart.createDefaultAxes();
    chart.setTitle("Simple line chart example");
    w.show();
    return a.exec();
}

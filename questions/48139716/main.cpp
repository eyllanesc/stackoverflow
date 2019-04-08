#include <QApplication>

#include <QtCharts>
using namespace QtCharts;

#include <QDebug>
#include <QOpenGLWidget>
#include <QPainter>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QWidget widget;
  widget.setLayout(new QVBoxLayout);

  QPushButton btn("save");
  QChartView chartView;

  widget.layout()->addWidget(&btn);
  widget.layout()->addWidget(&chartView);

  QLineSeries *series = new QLineSeries();
  series->setUseOpenGL(true); // this line cause a problem

  QLineSeries *series2 = new QLineSeries();

  constexpr double PI = 3.14159265359;
  for (int i = 0; i < 100; ++i) {
    double temp = i * PI / 6;
    series->append(temp, sin(temp));
  }

  for (int i = 0; i < 100; ++i) {
    double temp = i * PI / 6;
    series2->append(temp, cos(temp));
  }

  QChart *chart = new QChart();
  chart->legend()->hide();
  chart->addSeries(series);
  chart->addSeries(series2);
  chart->createDefaultAxes();
  chart->setTitle("Simple line chart example");

  chartView.setChart(chart);

  QObject::connect(&btn, &QPushButton::clicked, [&chartView] {
    QPixmap p = chartView.grab();
    QOpenGLWidget *glWidget = chartView.findChild<QOpenGLWidget *>();
    if (glWidget) {
      QPainter painter(&p);
      QPoint d =
          glWidget->mapToGlobal(QPoint()) - chartView.mapToGlobal(QPoint());
      painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
      painter.drawImage(d, glWidget->grabFramebuffer());
      painter.end();
    }
    p.save("test", "PNG");
  });
  widget.show();

  return a.exec();
}

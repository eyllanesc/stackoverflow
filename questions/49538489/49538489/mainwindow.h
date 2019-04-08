#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
using namespace QtCharts;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  bool eventFilter(QObject *watched, QEvent *event) override;
public slots:
  void rubberZoomAdapt(QPointF fp, QPointF tp);

signals:
  void rubberBandChanged(QPointF fp, QPointF tp);

private:
  Ui::MainWindow *ui;
  QChartView *qcvChart;
  QChart *chart;
  QRubberBand *rubberBand;
};

#endif // MAINWINDOW_H

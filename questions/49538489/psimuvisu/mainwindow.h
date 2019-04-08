#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chart.h"
#include "tickdata.h"
#include <QMainWindow>
#include <QResizeEvent>
#include <QtCharts>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void resizeEvent(QResizeEvent *event);
  void showEvent(QShowEvent *event);
  bool eventFilter(QObject *watched, QEvent *event);
  void callBack_newData();

private slots:
  void on_bStart_clicked();
  void on_bStop_clicked();
  void on_dVitesse_valueChanged(int value);
  void on_sZoom_valueChanged(int value);
  void on_bCursor_clicked();
  void on_bResetZoom_clicked();
  void on_sPosition_valueChanged(int value);
public slots:
  void signalTest(bool b);
  void rubberZoomAdapt(QPointF fp, QPointF tp);

signals:
  void rubberBandChanged(QPointF fp, QPoint tp);

private:
  Ui::MainWindow *ui;

  QChartView *qcvChart;
  Chart *chart;
  QRubberBand *qRubberBand;

  TickData *td1;

  int index;
  bool bCursorState;
  QRectF zoomAera;
  float scaledZoom;
  float positionZoom;
};

#endif // MAINWINDOW_H

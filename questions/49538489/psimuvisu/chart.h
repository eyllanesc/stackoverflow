#ifndef CHART_H
#define CHART_H

#include <QtCharts>

class Chart : public QChart {
  Q_OBJECT

public:
  Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
  virtual ~Chart();
  void resizeEvent(QResizeEvent *event);
  void addValue(float val);
  void setZoom(float scaledZoom);
  void resetZoom();
  void zoomInRubberBand();
  void setPosition(float positionZoom);
  void setPause(bool p);
public slots:
  void handleTimeout();

private:
  void refreshAxis();

  QTimer qtimer;
  QLineSeries *qlsSeries;
  QValueAxis *vaAxisX;
  QValueAxis *vaAxisY;
  QRectF *qZoomAera;
  QQueue<float> *qQueue;
  qreal xValue;
  qreal yValue;
  float xDelta;
  float xWidthAera;
  float zoom;
  bool noZoom;
  float positionZoom;
  bool pauseValue;
};

#endif /* CHART_H */

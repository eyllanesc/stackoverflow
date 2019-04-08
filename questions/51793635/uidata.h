#ifndef UIDATA_H
#define UIDATA_H

#include <QLineSeries>
#include <QObject>

QT_CHARTS_USE_NAMESPACE

class UiData : public QObject {
  Q_OBJECT
  Q_PROPERTY(QLineSeries *xy READ xy WRITE setXy NOTIFY xyChanged)
  Q_PROPERTY(qreal xmin READ xmin NOTIFY xminChanged)
  Q_PROPERTY(qreal xmax READ xmax NOTIFY xmaxChanged)
  Q_PROPERTY(qreal ymin READ ymin NOTIFY yminChanged)
  Q_PROPERTY(qreal ymax READ ymax NOTIFY ymaxChanged)
public:
  UiData(QObject *parent = nullptr);

  QLineSeries *xy() const;
  void setXy(QLineSeries *xy);

  qreal xmin() const;
  qreal xmax() const;
  qreal ymin() const;
  qreal ymax() const;

public slots:
  void newData(qreal x, qreal y);
signals:
  void xyChanged();
  void xminChanged();
  void xmaxChanged();
  void yminChanged();
  void ymaxChanged();

private:
  QLineSeries *mXy;
  qreal mXmin;
  qreal mXmax;
  qreal mYmin;
  qreal mYmax;
};

#endif // UIDATA_H

#ifndef UIDATA_H
#define UIDATA_H

#include <QObject>
#include <QLineSeries>

QT_CHARTS_USE_NAMESPACE

class UiData: public QObject{
    Q_OBJECT
    Q_PROPERTY(QLineSeries* xy READ xy WRITE setXy NOTIFY xyChanged)
    Q_PROPERTY(qreal xmin READ xmin WRITE setXmin NOTIFY xminChanged)
    Q_PROPERTY(qreal xmax READ xmax WRITE setXmax NOTIFY xmaxChanged)
    Q_PROPERTY(qreal ymin READ ymin WRITE setYmin NOTIFY yminChanged)
    Q_PROPERTY(qreal ymax READ ymax WRITE setYmax NOTIFY ymaxChanged)
public:
    UiData(QObject *parent=nullptr);

    QLineSeries *xy() const;
    void setXy(QLineSeries *xy);

    qreal xmin() const;
    void setXmin(const qreal &xmin);

    qreal xmax() const;
    void setXmax(const qreal &xmax);

    qreal ymin() const;
    void setYmin(const qreal &ymin);

    qreal ymax() const;
    void setYmax(const qreal &ymax);

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

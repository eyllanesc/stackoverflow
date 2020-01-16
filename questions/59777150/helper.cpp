#include "helper.h"

#include <QAbstractAxis>
#include <QAbstractSeries>
#include <QLineSeries>
#include <QMetaObject>
#include <QQuickItem>
#include <random>
#include <cstring>

QT_CHARTS_USE_NAMESPACE

void Helper::createSerie(QQuickItem *chartview){
    if(!chartview)
        return;
    const QMetaObject *mo = chartview->metaObject();
    if(std::strcmp(mo->className(), "QtCharts::DeclarativeChart") != 0)
        return;
    int ix = mo->indexOfEnumerator("SeriesType");
    QMetaEnum me = mo->enumerator(ix);
    int type = me.keyToValue("SeriesTypeLine");
    QAbstractAxis *axis_x = nullptr;
    QMetaObject::invokeMethod(chartview, "axisX", Qt::DirectConnection,
                              Q_RETURN_ARG(QAbstractAxis *, axis_x));
    QAbstractAxis *axis_y = nullptr;
    QMetaObject::invokeMethod(chartview, "axisY", Qt::DirectConnection,
                              Q_RETURN_ARG(QAbstractAxis *, axis_y));
    QAbstractSeries *serie = nullptr;
    QMetaObject::invokeMethod(chartview, "createSeries", Qt::DirectConnection,
                              Q_RETURN_ARG(QAbstractSeries *, serie),
                              Q_ARG(int, type),
                              Q_ARG(QString, "serie from c++"),
                              Q_ARG(QAbstractAxis *, axis_x),
                              Q_ARG(QAbstractAxis *, axis_y));
    if(QLineSeries *line_serie = qobject_cast<QLineSeries *>(serie)){
        static std::default_random_engine e;
        static std::uniform_real_distribution<> dis(0, 3);
        for(int i=0; i < 14; i++){
            line_serie->append(i, dis(e));
        }
    }
}

void Helper::removeAllSeries(QQuickItem *chartview){
    if(!chartview)
        return;
    const QMetaObject *mo = chartview->metaObject();
    if(std::strcmp(mo->className(), "QtCharts::DeclarativeChart") != 0)
        return;
    QMetaObject::invokeMethod(chartview, "removeAllSeries", Qt::DirectConnection);
}

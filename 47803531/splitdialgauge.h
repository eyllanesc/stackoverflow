#ifndef SPLITDIALGAUGE_H
#define SPLITDIALGAUGE_H

#include "limits_t.h"

#include <QPainter>
#include <QQuickPaintedItem>


class SplitDialGauge : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(LIMITS_T *limits READ getLimits WRITE setLimits NOTIFY limitsChanged)

public:
    SplitDialGauge(QQuickItem *parent = 0):QQuickPaintedItem(parent){
    }
    void paint(QPainter *painter){
        painter->fillRect(contentsBoundingRect(), Qt::red);
        //test
        painter->drawRect(0, 0, limits->readMin(), limits->readMin());
    }

    LIMITS_T *getLimits() const{
        return limits;
    }
    void setLimits(LIMITS_T *value){
        limits = value;
        connect(limits, &LIMITS_T::minChanged, [this](){
            update();
        });
        update();
        emit limitsChanged();
    }
private:
    LIMITS_T *limits;

signals:
    void limitsChanged();
};
#endif // SPLITDIALGAUGE_H


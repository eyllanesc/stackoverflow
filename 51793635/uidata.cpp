#include "uidata.h"


UiData::UiData(QObject *parent):
    QObject(parent),
    mXy(nullptr)
{

}

QLineSeries *UiData::xy() const
{
    return mXy;
}

void UiData::setXy(QLineSeries *xy)
{
    if(mXy == xy) return;
    if(mXy)
        if(mXy->parent() == this)
            delete mXy;
    mXy = xy;
    emit xyChanged();
}

qreal UiData::xmin() const{
    return mXmin;
}

void UiData::setXmin(const qreal &xmin)
{
    if(mXmin == xmin)
        return;
    mXmin = xmin;
    emit xminChanged();
}

qreal UiData::xmax() const
{
    return mXmax;
}

void UiData::setXmax(const qreal &xmax)
{
    if(mXmax == xmax)
        return;
    mXmax = xmax;
    emit xmaxChanged();
}

qreal UiData::ymin() const
{
    return mYmin;
}

void UiData::setYmin(const qreal &ymin)
{
    if(mYmin == ymin)
        return;
    mYmin = ymin;
    emit yminChanged();

}

qreal UiData::ymax() const
{
    return mYmax;
}

void UiData::setYmax(const qreal &ymax)
{
    if(mYmax == ymax)
        return;
    mYmax = ymax;
    emit ymaxChanged();
}

void UiData::newData(qreal x, qreal y){
    if(mXy){
        if(x > xmax())
            setXmax(x);
        else if (x < xmin())
            setXmin(x);

        if(y > ymax())
            setYmax(y);
        else if (y < ymin())
            setYmin(y);
        mXy->append(x, y);
    }
}



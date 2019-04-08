#include "uidata.h"

UiData::UiData(QObject *parent) : QObject(parent), mXy(nullptr) {}

QLineSeries *UiData::xy() const { return mXy; }

void UiData::setXy(QLineSeries *xy) {
  if (mXy == xy)
    return;
  if (mXy)
    if (mXy->parent() == this)
      delete mXy;
  mXy = xy;
  emit xyChanged();
}

qreal UiData::xmin() const { return mXmin; }

qreal UiData::xmax() const { return mXmax; }

qreal UiData::ymin() const { return mYmin; }

qreal UiData::ymax() const { return mYmax; }

void UiData::newData(qreal x, qreal y) {
  if (mXy) {

    if (x > mXmax) {
      mXmax = x;
      emit xmaxChanged();
    } else if (x < mXmin) {
      mXmin = x;
      emit xminChanged();
    }

    if (y > mYmax) {
      mYmax = y;
      emit ymaxChanged();
    } else if (y < mYmin) {
      mYmin = y;
      emit yminChanged();
    }
    mXy->append(x, y);
  }
}

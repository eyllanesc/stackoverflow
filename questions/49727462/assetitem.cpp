#include "assetitem.h"

QString AssetItem::name() const { return mName; }

void AssetItem::setName(const QString &name) { mName = name; }

QGeoCoordinate AssetItem::asset() const { return mAsset; }

void AssetItem::setAsset(const QGeoCoordinate &asset) {

  if (mAsset.isValid())
    appendHistory(mAsset);
  mAsset = asset;
}

void AssetItem::appendHistory(const QGeoCoordinate &value) { history << value; }

QList<QGeoCoordinate> AssetItem::getHistory() const { return history; }

QColor AssetItem::getColor() const { return mColor; }

void AssetItem::setColor(const QColor &color) { mColor = color; }

int AssetItem::getAngle() const { return mAngle; }

void AssetItem::setAngle(int angle) { mAngle = angle; }

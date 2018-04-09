#ifndef ASSETITEM_H
#define ASSETITEM_H

#include <QColor>
#include <QGeoCoordinate>
#include <QString>

class AssetItem{
public:
    QString name() const;
    void setName(const QString &name);

    QGeoCoordinate asset() const;
    void setAsset(const QGeoCoordinate &asset);

    void appendHistory(const QGeoCoordinate &value);
    QList<QGeoCoordinate> getHistory() const;

    QColor getColor() const;
    void setColor(const QColor &color);

private:
    QString mName;
    QGeoCoordinate mAsset;
    QList<QGeoCoordinate> history;
    QColor mColor;
};

#endif // ASSETITEM_H

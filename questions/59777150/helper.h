#ifndef HELPER_H
#define HELPER_H

#include <QObject>

class QQuickItem;

class Helper : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;
    Q_INVOKABLE void createSerie(QQuickItem *chartview);
    Q_INVOKABLE void removeAllSeries(QQuickItem *chartview);
};

#endif // HELPER_H

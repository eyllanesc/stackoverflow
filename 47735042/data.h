#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QPointF>
#include <QTimer>

class Data : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF wValue READ wValue NOTIFY wValueChanged)

public:
    Data(QObject *parent=Q_NULLPTR);
    QPointF wValue() const{
        return m_wValue;
    }
signals:
    void wValueChanged();
private slots:
    void wTimeout();
private:
    QTimer * m_wTimer;
    QPointF m_wValue;
};

#endif // DATA_H

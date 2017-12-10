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
    Data(QObject *parent=Q_NULLPTR):QObject(parent){
        m_wTimer = new QTimer(this);
        m_wTimer->setInterval((1000 / 5));
        connect(m_wTimer, &QTimer::timeout, this, &Data::wTimeout);
        m_wTimer->start();
    }
    QPointF wValue() const{
        return m_wValue;
    }
signals:
    void wValueChanged();

private slots:
    void wTimeout(){
        int HIGH = 100;
        int LOW = 0;
        int val = rand() % (HIGH - LOW + 1) + LOW;
        m_wValue.setX(m_wValue.x()+1);
        m_wValue.setY(val);
        emit wValueChanged();
    }

private:
    QTimer * m_wTimer;
    QPointF m_wValue;
};


#endif // DATA_H

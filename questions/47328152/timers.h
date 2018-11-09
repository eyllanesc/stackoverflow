#ifndef TIMERS_H
#define TIMERS_H

#include <QTimer>
#include <QDebug>

class Timers : public QTimer
{
public:
    Timers(QObject *parent = Q_NULLPTR):QTimer(parent){
        connect(this, &Timers::timeout, this, &Timers::onTimeout);
        setInterval(100);
    }
public slots:
    void onTimeout(){
        qDebug()<<"timeout";
    }
};

#endif // TIMERS_H

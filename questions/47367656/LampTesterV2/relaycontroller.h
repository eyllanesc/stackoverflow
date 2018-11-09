#ifndef RELAYCONTROLLER_H
#define RELAYCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <wiringPi.h>
#include <QDebug>

class RelayController : public QObject
{
    Q_OBJECT
public:
    explicit RelayController(int pin, QObject *parent = 0):QObject(parent){
        timer = new QTimer(this);
        state = false;
        timer->setInterval(750);
        mPin = pin;
        //old style
        connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
        //new style
        //connect(timer, &QTimer::timeout, this, &RelayController::onTimeout);

        pinMode (mPin, OUTPUT);
        relayLow();
        mCounter = 0;
    }
    void start(){
        qDebug()<<"start";
        timer->start();
    }
    void stop(){
        qDebug()<<"stop";
        timer->stop();
    }

    void relayLow(){
        digitalWrite (mPin, LOW);
        qDebug()<<"low";
    }
    void relayHigh(){
        //code here: relay on
        digitalWrite(mPin, HIGH);
        qDebug()<<"high";
    }
signals:
    void changeCounter(int counter);
private slots:
    void onTimeout(){
        if(state){
            relayHigh();
            mCounter++;
            emit changeCounter(mCounter);
        }
        else{
            relayLow();
        }
        state = !state;
    }
private:
    QTimer *timer;
    bool state;
    int mPin;
    int mCounter;
};


#endif // RELAYCONTROLLER_H


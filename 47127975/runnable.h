#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <QObject>
#include <QRunnable>
#include <QThread>

class Runnable : public QRunnable
{
    int mNumber = 0;
    QObject *mReceiver;
    bool mRunning;
public:
    Runnable(QObject *receiver){
        mReceiver = receiver;
        mRunning = false;
    }
    void run(){
        mRunning = true;
        while(mRunning){
            mNumber++;
            QMetaObject::invokeMethod(mReceiver, "setNumber",
                                      Qt::QueuedConnection,
                                      Q_ARG(int, mNumber));
            QThread::msleep(10);
        }
    }
    bool isRunning() const{
        return mRunning;
    }
    void stop(){
        mRunning = false;
    }
};

#endif // RUNNABLE_H

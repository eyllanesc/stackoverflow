#ifndef DATA_H
#define DATA_H

#include "runnable.h"

#include <QObject>
#include <QThreadPool>

class Data : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int number READ number WRITE setNumber NOTIFY numberChanged)
public:
    explicit Data(QObject *parent = nullptr):QObject(parent){
        m_number = 0;
        runnable = new Runnable(this);
    }
    ~Data(){
        runnable->stop();
    }
    Q_INVOKABLE void start(){
        if(!runnable->isRunning())
            QThreadPool::globalInstance()->start(runnable);
    }
    int number() const{
        return m_number;
    }
public slots:
    void setNumber(int number){
        if(number == m_number)
            return;
        m_number = number;
        emit numberChanged(m_number);
    }
signals:
    void numberChanged(int);
private:
    int m_number;
    Runnable *runnable;
};

#endif // DATA_H


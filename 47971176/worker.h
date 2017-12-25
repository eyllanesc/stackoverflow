#ifndef WORKER_H
#define WORKER_H

#include <QDebug>
#include <QStringList>
#include <QInputDialog>
#include <QThread>

class Worker : public QObject
{
    Q_OBJECT
    QObject *mGui;

public:
    explicit Worker(QObject *gui, QObject *parent = nullptr):QObject(parent){
        mGui = gui;
    }
    virtual ~Worker(){}

public slots:
    void start_work(){
        ask_user();
    }
    void ask_user(){
        QStringList choices;
        choices.append("one");
        choices.append("two");
        QString retVal;
        for(int i=0; i < 10; i++){
            QMetaObject::invokeMethod(mGui, "callGuiMethod", Qt::BlockingQueuedConnection,
                                      Q_RETURN_ARG(QString, retVal),
                                      Q_ARG(QStringList, choices));
            qDebug()<<retVal;
            QThread::sleep(5);
        }
    }

signals:
    void finished();
};

#endif // WORKER_H

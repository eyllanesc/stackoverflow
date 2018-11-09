#ifndef WIDGET_H
#define WIDGET_H

#include "worker.h"

#include <QThread>
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT
    QThread workerThread;
public:
    explicit Widget(QWidget *parent = nullptr):QWidget(parent){
        worker_create();
    }

    Q_INVOKABLE QString callGuiMethod(QStringList items){
        return QInputDialog::getItem(0, "title", "label", items , 0, false);
    }

    ~Widget() {
        workerThread.quit();
        workerThread.wait();
    }

public slots:
    void worker_create(){
        Worker *worker = new Worker(this);
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::started, worker, &Worker::start_work);
        connect(worker, &Worker::finished, worker, &QObject::deleteLater);
        connect(worker, &Worker::finished, &workerThread, &QThread::quit);
        connect(&workerThread, &QThread::finished, &workerThread, &QObject::deleteLater);
        workerThread.start();
    }
};

#endif // WIDGET_H

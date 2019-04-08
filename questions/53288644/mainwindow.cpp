#include "mainwindow.h"
#include <QDebug>
#include <iostream>

Worker::Worker() : t(this) {
  connect(&t, &QTimer::timeout, this, &Worker::process);
}

void Worker::process() { std::cout << "triggering timer" << std::endl; }

void Worker::startWorker() { t.start(1000); }

void Worker::stopProcess() {
  QMetaObject::invokeMethod(&t, "stop", Qt::QueuedConnection);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  wt.moveToThread(&workerThread);
  connect(&workerThread, &QThread::started, &wt, &Worker::startWorker);
  connect(&workerThread, &QThread::finished, &workerThread,
          &QObject::deleteLater);
  workerThread.start();
}

MainWindow::~MainWindow() {
  wt.stopProcess();
  workerThread.quit();
  workerThread.wait();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTimer>

class Worker : public QObject {
  Q_OBJECT
public:
  Worker();

private:
  QTimer t;
public slots:
  void process();
  void startWorker();
  void stopProcess();
};

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  QThread workerThread;
  Worker wt;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  de = new DataExchange;

  connect(de, &DataExchange::serialOnChanged, this, &MainWindow::mySlot);

  QTimer *timer = new QTimer(this);

  connect(timer, &QTimer::timeout, this,
          [=]() { de->set_serialOn(!de->get_serialOn()); });
  timer->start(1000);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::mySlot(bool value) { qDebug() << value; }

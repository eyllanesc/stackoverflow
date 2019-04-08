#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQmlContext>
#include <QQmlEngine>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->gaugeWidget->engine()->rootContext()->setContextProperty("MainWindow",
                                                               this);
  ui->gaugeWidget->setSource(QUrl("qrc:/gauge.qml"));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setDataToGauge(double newVal) {
  emit dataGaugeChanged(newVal);
}

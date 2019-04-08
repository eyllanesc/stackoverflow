#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QQmlContext>
#include <QQmlEngine>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->quickWidget->setSource(QUrl("qrc:/main.qml"));
  ui->quickWidget->engine()->rootContext()->setContextProperty("test",
                                                               &testObj);
}

MainWindow::~MainWindow() { delete ui; }

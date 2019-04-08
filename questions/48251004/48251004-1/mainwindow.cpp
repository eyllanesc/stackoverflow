#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QQmlContext>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->quickWidget->rootContext()->setContextProperty("lineEdit", ui->lineEdit);
}

MainWindow::~MainWindow() { delete ui; }

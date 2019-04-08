#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->listWidget, SIGNAL(blankSpaceClicked()), this, SLOT(print()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::print() { qDebug() << "blankSpaceClicked"; }

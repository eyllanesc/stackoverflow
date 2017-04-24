#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTabWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::onTabCloseRequested);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTabCloseRequested(int index)
{
   qDebug()<<ui->tabWidget->tabText(index);
   ui->tabWidget->removeTab(index);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->widget, &DoubleClickedWidget::doubleClicked, this, &MainWindow::onDoubleClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDoubleClicked()
{
    qDebug()<<"double clicked";
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartStreamingButton_clicked()
{
    ui->camera->startStreaming();
}

void MainWindow::on_CheckCamerasButton_clicked()
{
    ui->camera->stopStreaming();
}

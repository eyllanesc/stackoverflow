#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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

void MainWindow::setUser(const User& user)
{
    mUser = user;
    qDebug()<<mUser.toString();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    emit Logout();
}

void MainWindow::on_pushButton_clicked()
{
    emit Logout();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTreeWidget>
#include <QDebug>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->treeWidget, &QTreeWidget::clicked, this, &QMainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}


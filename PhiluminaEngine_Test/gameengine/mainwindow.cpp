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

    //connects all the objects with the needed slots
    //connect(ui->treeWidget, &QTreeWidget::clicked, this, &QMainWindow::close);
    connect(ui->treeWidget, &QTreeWidget::clicked, this, &QMainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}


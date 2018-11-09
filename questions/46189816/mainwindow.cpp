#include "htmldelegate.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setItemDelegate(new HtmlDelegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

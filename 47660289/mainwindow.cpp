#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tuto = new TutoWidget(this);
    setFixedSize(640, 480);
    tuto->addPage(QPoint(200, 200), 40, QPoint(100, 100), "some text1");
    tuto->addPage(QPoint(300, 300), 60, QPoint(200, 100), "some text2");
    tuto->addPage(QPoint(100, 200), 100, QPoint(200, 50), "some text3");
    tuto->addPage(QPoint(200, 100), 80, QPoint(100, 200), "some text4");
}

MainWindow::~MainWindow()
{
    delete ui;
}

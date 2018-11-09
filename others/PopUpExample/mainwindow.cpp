#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    popup = new PopUp(this);
    popup->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::movePopUp()
{
    QPoint p = mapToGlobal(QPoint(size().width(), size().height())) -
            QPoint(popup->size().width(), popup->size().height());
    popup->move(p);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    movePopUp();
    QMainWindow::resizeEvent(event);
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    movePopUp();
    QMainWindow::moveEvent(event);
}

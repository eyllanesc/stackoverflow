#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fCar = new Car(TwoVector(150, 2), 4);


    QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(paintEvent()));
    connect(timer, SIGNAL(timeout()), this, SLOT(Drive()));
    timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Drive()
{
    fCar->Drive(fCar->GetVelocity());
    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen DotPen(Qt::red);
    DotPen.setWidth(10);

    painter.setPen(DotPen);
    painter.drawPoint((fCar->GetPosition().GetRadius())*(cos(fCar->GetPosition().GetAngle()))
                      , (fCar->GetPosition().GetRadius())*(sin(fCar->GetPosition().GetAngle())));
}

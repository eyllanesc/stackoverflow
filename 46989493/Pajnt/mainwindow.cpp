#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>

int mSelection = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mPix = QPixmap(400,400);
    mPix.fill(Qt::white);
    mPressed = false;
    drawStarted = false;
    mColor = QColor(Qt::black);
    mSize = 2;


    toolWindow.setWindowFlags(Qt::SubWindow | Qt::WindowDoesNotAcceptFocus);
    toolWindow.show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.drawPixmap(0,0,mPix);

    QPen pen(mColor);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(mSize);
    painter.setPen(pen);

    if(mPressed)
    {
        if(mSelection == 2)
            painter.drawRect(mRect);
        else if(mSelection == 4) {
            painter.drawLine(mLine);
        }
        drawStarted = true;
    } else if (drawStarted){
        QPainter tempPainter(&mPix);
        tempPainter.setPen(pen);
        if(mSelection == 2)
            tempPainter.drawRect(mRect);
        else if(mSelection == 4) {
            tempPainter.drawLine(mLine);
        }
        painter.drawPixmap(0,0,mPix);
    }
    painter.end();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mPressed = true;
    mBegin = event->pos();
    if(mSelection == 2){
        mRect.setTopLeft(event->pos());
        mRect.setBottomRight(event->pos());
    }
    else if(mSelection == 4){
        mLine.setP1(event->pos());
        mLine.setP2(event->pos());
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPen pen(mColor);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(mSize);
    switch(mSelection)
    {
    case 1:
        {
            QPainter penPainter(&mPix);
            penPainter.setPen(pen);
            mEnd = event->pos();
            penPainter.drawLine(mBegin, mEnd);
            mBegin = mEnd;
            update();
            break;
        }
    case 2:
        {
            mRect.setBottomRight(event->pos());
            update();
            break;
        }
    case 4:
        {
            mLine.setP2(event->pos());
            update();
            break;
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    mPressed = false;
    update();
}


#include "timeline.h"
#include "trackwindow.h"
#include "ui_trackwindow.h"

#include <QGraphicsView>

TrackWindow::TrackWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrackWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene);
    auto timeline = new TimeLine(new Timers);
    ui->graphicsView->scene()->addItem(timeline);
}

TrackWindow::~TrackWindow()
{
    delete ui;
}

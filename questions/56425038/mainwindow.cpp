#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQmlContext>
#include <QTimer>
#include <cmath>

const double pi = std::acos(-1);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->quickWidget->rootContext()->setContextProperty("marker_model", &marker_model);
    ui->quickWidget->setSource(QUrl("qrc:/mapview.qml"));
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimeout);
    timer->start(1000);
    marker_model.setMaxMarkers(5);
    marker_model.moveMarker(QGeoCoordinate(15.4561, 73.8021));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimeout()
{
    double x = 15.4561 + 0.01*std::sin(i*pi/24);
    double y = 73.8021 + 0.01*std::cos(i*pi/24);
    QGeoCoordinate next(x, y);
    marker_model.moveMarker(next);
    i++;
}

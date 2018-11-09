#include "mainwindow.h"
#include "relayframe.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>
#include <wiringPi.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wiringPiSetup();

    QVBoxLayout *lay = new QVBoxLayout(ui->centralWidget);

    const int pins[] = {0, 1, 2, 3, 4, 5}; // pins
    for(int i=0; i < 7; i++){
        RelayFrame *relay = new RelayFrame(pins[i], ui->centralWidget);
        lay->addWidget(relay);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}




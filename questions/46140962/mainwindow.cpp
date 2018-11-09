#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QTextEdit>
#include <QDebug>
#include <QFile>
#include <QApplication>

#define FORMAT  "hh:mm:ss"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->fromTimeEdit->setDisplayFormat(FORMAT);
    ui->toTimeEdit->setDisplayFormat(FORMAT);
    ui->toTimeEdit->setTime(QTime::fromString("23:59:59", FORMAT));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QTime from =  ui->fromTimeEdit->time();
    QTime to = ui->toTimeEdit->time();

    bool copyLog = false;
    if(from <= to){
        QFile file("/home/qhipa/Downloads/kaynak.log");
        ui->textEdit->clear();
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){

            QTextStream in(&file);
            while(!in.atEnd()){
                QString line = in.readLine();
                QString dateLogStr = line.left(8);
                QTime timeLog = QTime::fromString(dateLogStr, FORMAT);
                if(timeLog.isValid()){
                    copyLog = timeLog >= from && timeLog <= to;
                }
                if(copyLog){
                    ui->textEdit->append(line);
                    QApplication::processEvents();
                }
            }
        }
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->lineEdit->setText("Mall Cop");

    //QLabel* pLabel = new QLabel;
    //pLabel->setStyleSheet("QLabel { Background-color: rgb(44, 62, 80); color : white; }");
    //this->setStyleSheet("Background-color: rgb(44, 62, 80);");

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::sendRequest() {
    QEventLoop eventLoop;
    QNetworkAccessManager manager;

    connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req(QUrl("http://www.omdbapi.com/?t="+ui->lineEdit->text()));
    QNetworkReply *reply = manager.get(req);
    eventLoop.exec();
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

    if(document.isObject()){
        moviescreen.setObject(document.object());
    }
}

// Search Button
void MainWindow::on_pushButton_clicked() {
    sendRequest();
    moviescreen.show();
    this->hide();
}

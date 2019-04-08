#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(&manager, &QNetworkAccessManager::finished, this,
          &MainWindow::onManagerFinished);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
  QNetworkRequest request(QUrl("http://hapi.fhir.org/baseDstu3/Patient"));
  request.setRawHeader("Content-Type", "application/fhir+json");
  QFile file("themostsimplepatientJSON.json");
  if (file.open(QIODevice::ReadOnly)) {
    manager.post(request, file.readAll());
  }
}

void MainWindow::onManagerFinished(QNetworkReply *reply) {
  qDebug() << reply->readAll();
}

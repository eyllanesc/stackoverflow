#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->lineEdit->setText("Mall Cop");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::sendRequest() {
  QEventLoop eventLoop;
  QNetworkAccessManager manager;

  connect(&manager, &QNetworkAccessManager::finished, &eventLoop,
          &QEventLoop::quit);
  QNetworkRequest req(
      QUrl("http://www.omdbapi.com/?t=" + ui->lineEdit->text()));
  QNetworkReply *reply = manager.get(req);
  eventLoop.exec();
  QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

  if (document.isObject()) {
    moviescreen.setObject(document.object());
  }
}

// Search Button
void MainWindow::on_pushButton_clicked() {
  sendRequest();
  moviescreen.show();
  this->hide();
}
